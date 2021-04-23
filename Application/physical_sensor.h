/*
 * physical_sensor.h
 *
 *  Created on: Apr 16, 2021
 *      Author: georg
 */

#ifndef APPLICATION_PHYSICAL_SENSOR_H_
#define APPLICATION_PHYSICAL_SENSOR_H_


#include "Board.h"


enum DataT{
    Pressure,
    Humidity,
    CPU,
    LAST
};

typedef struct Pressure_Data {
    uint32_t center_point_timestamp;
    uint32_t pressure;
    uint32_t temperature;
} Pressure_Data;
typedef struct Humidity_Data {
    uint32_t center_point_timestamp;
    uint16_t humidity;
    uint16_t temperature;
} Humidity_Data;
typedef struct cpu_data {
    uint32_t center_point_timestamp;
    uint16_t voltage_BatteryChannel;
    uint16_t voltage_DCOUPL;
    uint16_t voltage_GROUND;
    uint16_t voltage_Battery_DIO13;
    uint16_t batMon;
    uint16_t temperature;
} cpu_data;

extern const int sizeof_data[LAST];

typedef union OneMeasurment{
    Pressure_Data pressure;
    Humidity_Data humidity;
    cpu_data cpu;
} OneMeasurment;


extern void GPIO_write(uint_least8_t index, unsigned int value);

OneMeasurment pop_data(enum DataT array);
void push_data(enum DataT array, OneMeasurment oneMeasure);
unsigned int data_count(enum DataT array);
unsigned int space_count_left(enum DataT array);

void physical_sensor_init(void);
void physical_sensor_process(void);





#endif /* APPLICATION_PHYSICAL_SENSOR_H_ */
