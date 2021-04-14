/*
 * board_control.c
 *
 *  Created on: Apr 13, 2021
 *      Author: georg
 */



#include <xdc/std.h>

#include <ti/drivers/PIN.h>
#include <ti/drivers/dpl/HwiP.h>

#include "Board.h"
#include "util_timer.h"
#include "board_control.h"


static PIN_State gpioPinState;
static PIN_Handle gpioPinHandle;

void Board_Gpio_initialize(void)
{
    gpioPinHandle = PIN_open(&gpioPinState, BoardGpioInitTable);

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
}
