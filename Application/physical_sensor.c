/*
 * physical_sensor.c
 *
 *  Created on: Apr 16, 2021
 *      Author: georg
 */



#include "physical_sensor.h"
#include <xdc/runtime/Timestamp.h>
#include <ti/sysbios/knl/Task.h>
#include <GPIO.h>

#include <ti/drivers/utils/RingBuf.h>

//1 second = 1000 ms
//1000 ms / 10 us = 100,000


#define SLEEP_TIME_TICK_COUNT (100000)
#define STORAGE_POINTS 256

RingBuf_Object buf_pressure, buf_humidity;


typedef struct Pressure_Data {
    uint32_t center_point_timestamp;
    uint32_t pressure;
    uint32_t temperature;
} Pressure_Data;
typedef struct Humidity_Data {
    uint32_t center_point_timestamp;
    uint16_t humidity;
    uint16_t temperature;
} Humidity_data;

Pressure_Data storage_of_pressure[STORAGE_POINTS];
Humidity_data storage_of_humidity[STORAGE_POINTS];
static I2C_Handle      i2c_handle;

void physical_sensor_init(void)
{
    RingBuf_construct(&buf_pressure,(unsigned char*)storage_of_pressure,sizeof(storage_of_pressure));
    RingBuf_construct(&buf_humidity,(unsigned char*)storage_of_humidity,sizeof(storage_of_humidity));

    I2C_init();
}
void physical_sensor_process(void)
{
    I2C_Transaction i2cTransaction;
    char r_buff[8];
    char w_buff[8];
    i2cTransaction.readBuf=r_buff;
    i2cTransaction.writeBuf=w_buff;

    GPIO_write(Sensor_Power,1); //enable power
    i2c_handle = I2C_open(Board_I2C, NULL);
    Task_sleep(25); //250 uS
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

    Task_sleep(1700);
    //read both
    w_buff[0]=0x10;
    i2cTransaction.readCount = 6;
    status = I2C_transfer(i2c_handle, &i2cTransaction);
    //assert?
    //XXX-add to ring buffer
    uint32_t timestamp = Timestamp_get32();

    System_printf("%i,%i,%i,%i,%i,%i,%i \r\n",timestamp,r_buff[0],r_buff[1],r_buff[2],r_buff[3],r_buff[4],r_buff[5]);

    i2cTransaction.writeCount = 0;
    status = I2C_transfer(i2c_handle, &i2cTransaction);
    //assert?
    //XXX-add to ring buffer
    System_printf("%i,%i,%i,%i,%i,%i,%i \r\n",timestamp,r_buff[0],r_buff[1],r_buff[2],r_buff[3],r_buff[4],r_buff[5]);






    I2C_close(i2c_handle); //close I2C so we can SLEEP!
    GPIO_write(Sensor_Power,0); //disable power
    Task_sleep(SLEEP_TIME_TICK_COUNT);
}
