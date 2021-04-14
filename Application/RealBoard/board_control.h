/*
 * board_control.h
 *
 *  Created on: Apr 13, 2021
 *      Author: georg
 */

#ifndef APPLICATION_REALBOARD_BOARD_CONTROL_H_
#define APPLICATION_REALBOARD_BOARD_CONTROL_H_



#if !defined(COPROCESSOR)
#include "config.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

void Board_Gpio_initialize(void);
void Board_Gpio_control(board_gpio_type gpio, uint32_t value);



typedef enum
{
    board_led_type_LED1,
    board_led_type_LED2,
    NO_OF_LEDS,
} board_led_type;

/*! LED States */
typedef enum
{
    board_led_state_OFF,
    board_led_state_ON,
    board_led_state_BLINK,
    board_led_state_BLINKING,
} board_led_state;


void Board_Led_initialize(void);
void Board_Led_control(board_led_type led, board_led_state state);
void Board_Led_toggle(board_led_type led);


#ifdef __cplusplus
}
#endif



#endif /* APPLICATION_REALBOARD_BOARD_CONTROL_H_ */
