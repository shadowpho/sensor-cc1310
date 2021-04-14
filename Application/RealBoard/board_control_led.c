/*
 * board_control_led.c
 *
 *  Created on: Apr 13, 2021
 *      Author: georg
 */


#include <xdc/std.h>

#include <ti/drivers/PIN.h>
#include <ti/drivers/dpl/HwiP.h>

#include "Board.h"
#include "util_timer.h"
#include "board_control_led.h"

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

