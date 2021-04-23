/*
 * physical_sensor.c
 *
 *  Created on: Apr 16, 2021
 *      Author: georg
 */

#include <ti/drivers/utils/RingBuf.h>
#include <ti/drivers/ADC.h>

//111'0000 W/R
//250 uS bootup time
//12 ms measurment (high quality)
//1MHz max comm
//0x7866 gogo read tempearture and humidity, normal more, temperature firs, no clock stretch
//we can read status and if nack then not ready
//then we read 2b T, 1B CRC, 2b PH, 1B CRC
#define SHTC3 0x70

//400 khz max
//400 us bootup time
//111'0111 W/R
//OSR timing: 4096(000) = 131 ms, 2048(001) = 66ms, 1024 (010) = 33ms, 512(011) = 16.4 ms
//run measurment both: 010_OSR_00
//w 0x10 to read both, r6
#define HP203B 0x77



#include "physical_sensor.h"
#include <xdc/runtime/Timestamp.h>
#include <ti/sysbios/knl/Task.h>
#include <GPIO.h>

#include <ti/drivers/utils/RingBuf.h>
#include <xdc/runtime/System.h>

#include <ti\devices\cc13x0\driverlib\aon_batmon.h>

//1 second = 1000 ms
//1000 ms / 10 us = 100,000
#define SLEEP_TIME_TICK_COUNT (100000)
#define STORAGE_POINTS 256
#define BATTERY_MEASURMENT_DIVIDE 60

RingBuf_Object RingBuffers[LAST];


Pressure_Data storage_of_pressure[STORAGE_POINTS];
Humidity_Data storage_of_humidity[STORAGE_POINTS];
cpu_data storage_of_cpu[STORAGE_POINTS/BATTERY_MEASURMENT_DIVIDE+1];


const int sizeof_data[LAST] = {sizeof(Pressure_Data), sizeof(Humidity_Data), sizeof(cpu_data)};

union OneMeasurment pop_data(enum DataT array)
{
    //XXX too little data
    int count_copied=0;
    union OneMeasurment return_measurment;
    while(count_copied<sizeof_data[array])
    {

        RingBuf_get(&(RingBuffers[array]),((unsigned char*) &return_measurment)+count_copied);
        count_copied++;
    }
    return return_measurment;
}
void push_data(enum DataT array, union OneMeasurment oneMeasure)
{
    //XXX too much data
    char buff;
    int count_copied=0;
    while(count_copied<sizeof_data[array])
    {
        buff = ((unsigned char*) &oneMeasure)[count_copied]; //XXX oh god i hope this works.
        RingBuf_put(&(RingBuffers[array]),buff);
        count_copied++;
    }
}
unsigned int data_count(enum DataT array)
{
    ///XXX throw if array>=LAST
    return (RingBuffers[array].count)/sizeof_data[array];
}
unsigned int space_count_left(enum DataT array)
{
    ///XXX throw if array>=LAST
    return (RingBuffers[array].maxCount - RingBuffers[array].count)/sizeof_data[array];
}

static I2C_Handle      i2c_handle;

void physical_sensor_init(void)
{

    RingBuf_construct(&(RingBuffers[0]),(unsigned char*)storage_of_pressure,sizeof(storage_of_pressure));
    RingBuf_construct(&(RingBuffers[1]),(unsigned char*)storage_of_humidity,sizeof(storage_of_humidity));
    RingBuf_construct(&(RingBuffers[2]),(unsigned char*)storage_of_cpu,sizeof(storage_of_cpu));
    I2C_init();
    ADC_init();
}


void collect_humidity_pressure()
{
    OneMeasurment temp_Storage;
    I2C_Transaction i2cTransaction;
    char r_buff[8];
    char w_buff[8];
    i2cTransaction.readBuf=r_buff;
    i2cTransaction.writeBuf=w_buff;

    GPIO_write(Sensor_Power,1); //enable power
    Task_sleep(100); //1 ms TBD
    i2c_handle = I2C_open(Board_I2C, NULL);
    Task_sleep(325); //3 ms TBDs
    //talk to
    i2cTransaction.slaveAddress = SHTC3;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readCount = 0;
    w_buff[0]=0x78;
    w_buff[1]=0x66;
    bool status = I2C_transfer(i2c_handle, &i2cTransaction);
    //assert?

    Task_sleep(15);
    i2cTransaction.writeCount = 1;
    i2cTransaction.slaveAddress = HP203B;
    w_buff[0]=0x4C;
    status = I2C_transfer(i2c_handle, &i2cTransaction);

    Task_sleep(1700);
    i2cTransaction.writeCount = 0;
    i2cTransaction.readCount = 6;
    i2cTransaction.slaveAddress = SHTC3;
    status = I2C_transfer(i2c_handle, &i2cTransaction);
    //assert?
    //XXX-add to ring buffer
    uint32_t timestamp = Timestamp_get32();

    System_printf("%i,%i,%i,%i,%i,%i,%i \r\n",timestamp,r_buff[0],r_buff[1],r_buff[2],r_buff[3],r_buff[4],r_buff[5]);
    temp_Storage.humidity.center_point_timestamp = timestamp;
    temp_Storage.humidity.humidity =  r_buff[1] + ((int)r_buff[0])<<8;
    temp_Storage.humidity.temperature = r_buff[4] + ((int)r_buff[3])<<8;
    push_data(Humidity,temp_Storage);
    //read both
    w_buff[0]=0x10;
    i2cTransaction.writeCount = 1;
    i2cTransaction.slaveAddress = HP203B;
    status = I2C_transfer(i2c_handle, &i2cTransaction);
    //assert?
    //XXX-add to ring buffer
    System_printf("%i,%i,%i,%i,%i,%i,%i \r\n",timestamp,r_buff[0],r_buff[1],r_buff[2],r_buff[3],r_buff[4],r_buff[5]);
    temp_Storage.pressure.pressure =r_buff[5] + ((int32_t)r_buff[4])<<8 + ((int32_t)r_buff[3])<<16;
    temp_Storage.pressure.temperature= r_buff[2] + ((int32_t)r_buff[1])<<8 + ((int32_t)r_buff[0])<<16;
    push_data(Pressure,temp_Storage);

    I2C_close(i2c_handle); //close I2C so we can SLEEP!
    GPIO_write(Sensor_Power,0); //disable power
}

int16_t get_adc_calibrated_read(int channel)
{
    uint16_t res;
    ADC_Handle adc = ADC_open(channel, NULL);
    ADC_convert(adc,&res);
    int16_t ret_value = (ADC_convertToMicroVolts(adc,res)>>16);
    ADC_close(adc);
    return ret_value;
}
void get_internal_sensors(void)
{
    OneMeasurment t_data;
    AONBatMonEnable();

    t_data.cpu.center_point_timestamp = Timestamp_get32();

    t_data.cpu.voltage_BatteryChannel=get_adc_calibrated_read(ADC_BatteryChannel);
    t_data.cpu.voltage_DCOUPL=get_adc_calibrated_read(ADC_DCOUPL);
    t_data.cpu.voltage_GROUND=get_adc_calibrated_read(ADC_GROUND);
    t_data.cpu.voltage_Battery_DIO13=get_adc_calibrated_read(Board_DIO13_Batt);


    t_data.cpu.batMon=AONBatMonBatteryVoltageGet();
    t_data.cpu.temperature=AONBatMonTemperatureGetDegC();
    push_data(CPU,t_data);
    AONBatMonDisable(); //let's hope it was allways disabled
}

static int run_count=0;
void physical_sensor_process(void)
{

    collect_humidity_pressure();

    if(run_count++ > BATTERY_MEASURMENT_DIVIDE)
    {
        //XXX - voltage and battery1 and battery2 and internal temp measurment
        run_count=0;
        get_internal_sensors();

    }

    Task_sleep(SLEEP_TIME_TICK_COUNT);
}
