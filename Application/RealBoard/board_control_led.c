/*
 * board_control_led.c
 *
 *  Created on: Apr 13, 2021
 *      Author: georg
 */


#include <xdc/std.h>


#include <ti/drivers/dpl/HwiP.h>
#include <string.h>
#include <xdc/runtime/System.h>

#define MAX_LCD_BUF 40
static uint8_t lcdBuf[MAX_LCD_BUF];


#include "board_control_led.h"

static void board_led_blinkTimeoutCB(UArg a0);
static bool board_led_anyBlinking(void);
static void board_led_blinkLed(void);
static unsigned int board_led_convertLedType(board_led_type led);
static uint32_t board_led_convertLedValue(board_led_state state);
static bool board_led_anyBlinking(void);
static bool board_led_anyBlinking(void)
{
    uint8_t x;

    for(x = 0; x < NO_OF_LEDS; x++)
    {
        if((ledStatus[x].state == board_led_state_BLINKING) ||
                        ((ledStatus[x].state == board_led_state_BLINK)
                        && (ledStatus[x].status != BLINKING_STATUS_DONE)))
        {
            return (true);
        }
    }

    return (false);
}

void Board_Led_control(board_led_type led, board_led_state state)
{

    unsigned int gpioType;
    uint32_t value;
    uint32_t key;

    if (ledPinHandle == NULL)
    {
        return;
    }

    if((led >= NO_OF_LEDS) || (state > board_led_state_BLINKING))
    {
        return;
    }

    /* Save state and status */
    ledStatus[led].state = state;
    if((state == board_led_state_BLINK) || (state == board_led_state_BLINKING))
    {
        ledStatus[led].status = BLINKING_STATUS_ON;
    }

    /* Enter critical section so this function is thread safe*/
    key = HwiP_disable();

    /* Update hardware LEDs */
    PIN_setOutputValue(ledPinHandle, gpioType, value);

    /* Exit critical section */
    HwiP_restore(key);


    /* Are any LEDs are blinking? */
    if(board_led_anyBlinking())
    {
        if(Timer_isActive(&blinkClkStruct) == false)
        {
            Timer_start(&blinkClkStruct);
        }
    }
    else
    {
        if(Timer_isActive(&blinkClkStruct) == true)
        {
            Timer_stop(&blinkClkStruct);
        }
    }
}



static void board_led_blinkTimeoutCB(UArg a0)
{
    /* Update blinking LEDs */
    board_led_blinkLed();

    if(board_led_anyBlinking())
    {
        /* Setup for next time */
        Timer_start(&blinkClkStruct);
    }
}

void Board_Led_initialize(void)
{
    uint8_t x;
    unsigned int index;
    uint32_t value;

    /* Open LED PIN driver */
    ledPinHandle = PIN_open(&ledPinState, ledPinTable);

    value = board_led_convertLedValue(board_led_state_OFF);

    for(x = 0; x < NO_OF_LEDS; x++)
    {
        ledStatus[x].state = board_led_state_OFF;
        ledStatus[x].status = BLINKING_STATUS_DONE;

        index = board_led_convertLedType((board_led_type) x);

        PIN_setOutputValue(ledPinHandle, index, value);
    }

    Timer_construct(&blinkClkStruct, board_led_blinkTimeoutCB,
    100,
                        0, false, 0);
}


static void board_led_blinkLed(void)
{
    uint8_t x;
    uint32_t key;

    for(x = 0; x < NO_OF_LEDS; x++)
    {
        unsigned int index;
        uint32_t value;

        if(ledStatus[x].state == board_led_state_BLINKING)
        {
            index = board_led_convertLedType((board_led_type) x);

            if(ledStatus[x].status == BLINKING_STATUS_OFF)
            {
                value = board_led_convertLedValue(board_led_state_ON);
                ledStatus[x].status = BLINKING_STATUS_ON;
            }
            else
            {
                value = board_led_convertLedValue(board_led_state_OFF);
                ledStatus[x].status = BLINKING_STATUS_OFF;
            }

            /* Enter critical section so this function is thread safe*/
            key = HwiP_disable();

            PIN_setOutputValue(ledPinHandle, index, value);

            /* Exit critical section */
            HwiP_restore(key);
        }
        else if((ledStatus[x].state == board_led_state_BLINK) && (ledStatus[x]
                        .status
                                                                  != BLINKING_STATUS_DONE))
        {
            index = board_led_convertLedType((board_led_type) x);
            value = board_led_convertLedValue(board_led_state_OFF);
            ledStatus[x].status = BLINKING_STATUS_DONE;

            /* Enter critical section so this function is thread safe*/
            key = HwiP_disable();

            PIN_setOutputValue(ledPinHandle, index, value);

            /* Exit critical section */
            HwiP_restore(key);
        }
    }
}


static unsigned int board_led_convertLedType(board_led_type led)
{
    if (led == board_led_type_LED1)
    {
        return(Board_PIN6);
    }
    return(Board_PIN8);
}

static uint32_t board_led_convertLedValue(board_led_state state)
{
    uint32_t value;

    switch(state)
    {
        case board_led_state_ON:
        case board_led_state_BLINK:
        case board_led_state_BLINKING:
            value = Board_GPIO_LED_ON;
            break;

        default:
            value = Board_GPIO_LED_OFF;
            break;
    }

    return (value);
}

void Board_Led_toggle(board_led_type led)
{
    board_led_state newState = board_led_state_OFF;

    /* Look for invalid parameter */
    if(led < NO_OF_LEDS)
    {
        if( (ledStatus[led].state != board_led_state_BLINK) &&
            (ledStatus[led].state != board_led_state_BLINKING) )
        {
            /* Toggle state */
            if(ledStatus[led].state == board_led_state_OFF)
            {
                newState = board_led_state_ON;
            }

            /* Set new state */
            Board_Led_control(led, newState);
        }
    }
}


void Board_Lcd_writeString(char *str, uint8_t line)
{
    System_printf(str);
    System_printf("\r\n");
}

extern void Util_itoa(uint16_t num, uint8_t *buf, uint8_t radix);
void Board_Lcd_writeStringValue(char *str, uint16_t value, uint8_t format,
                                uint8_t line)
{
    int len = strlen(str);
    memset(lcdBuf, 0, MAX_LCD_BUF);
    memcpy(lcdBuf, str, len);
    Util_itoa(value, &lcdBuf[len], format);


    System_printf((xdc_CString)lcdBuf);
    System_printf("\r\n");
}
