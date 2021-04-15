/*
 * board_control_led.h
 *
 *  Created on: Apr 13, 2021
 *      Author: georg
 */

#ifndef APPLICATION_REALBOARD_BOARD_CONTROL_LED_H_
#define APPLICATION_REALBOARD_BOARD_CONTROL_LED_H_

#include "Board.h"
#include "util_timer.h"
#include <ti/drivers/PIN.h>


#ifdef __cplusplus
extern "C"
{
#endif


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



typedef enum
{
    BLINKING_STATUS_ON,
    BLINKING_STATUS_OFF,
    BLINKING_STATUS_DONE
} blinkStatus;

/******************************************************************************
 Typedefs
 *****************************************************************************/

typedef struct
{
    board_led_state state; /* Off, On or Blink */
    blinkStatus status; /* What is led status (on, off, or done) */
} board_led_status_t;

static Clock_Struct blinkClkStruct;

static board_led_status_t ledStatus[NO_OF_LEDS];

static PIN_Config ledPinTable[] =
{
             Board_PIN6 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL
            | PIN_DRVSTR_MAX, /* LED1 initially off */
            Board_PIN8 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL
            | PIN_DRVSTR_MAX, /* LED2 initially off */
    /* To Do */
    /* LED2 and LED3 should be added later */
    PIN_TERMINATE /* Terminate list     */
};

/* LED pin state */
static PIN_State ledPinState;

/* LED Pin Handle */
static PIN_Handle ledPinHandle;





void Board_Led_initialize(void);
void Board_Led_control(board_led_type led, board_led_state state);
void Board_Led_toggle(board_led_type led);


#define LCD_WRITE_STRING(str, line) Board_Lcd_writeString(str, line)
/*! Macro definition to write a string with a value to the LCD */
#define LCD_WRITE_STRING_VALUE(str, value, format, line) \
    Board_Lcd_writeStringValue(str, value, format, line)


extern void Board_Lcd_writeString(char *str, uint8_t line);


extern void Board_Lcd_writeStringValue(char *str, uint16_t value,
                                       uint8_t format,
                                       uint8_t line);



#ifdef __cplusplus
}
#endif



#endif /* APPLICATION_REALBOARD_BOARD_CONTROL_LED_H_ */
