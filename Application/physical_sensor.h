/*
 * physical_sensor.h
 *
 *  Created on: Apr 16, 2021
 *      Author: georg
 */

#ifndef APPLICATION_PHYSICAL_SENSOR_H_
#define APPLICATION_PHYSICAL_SENSOR_H_


#include "Board.h"

extern void GPIO_write(uint_least8_t index, unsigned int value);

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

void physical_sensor_init(void);
void physical_sensor_process(void);


#endif /* APPLICATION_PHYSICAL_SENSOR_H_ */
