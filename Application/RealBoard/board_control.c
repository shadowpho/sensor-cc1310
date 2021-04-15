/*
 * board_control.c
 *
 *  Created on: Apr 13, 2021
 *      Author: georg
 */



#include <xdc/std.h>

#include <ti/drivers/PIN.h>
#include <ti/drivers/dpl/HwiP.h>


#include "board_control.h"

void Board_Gpio_initialize()
{
    return; //already done in board_init...
}

void Board_Key_initialize()
{
    return; //already done in board_init...
}

CryptoCC26XX_Object cryptoCC26XXObjects[1];

const CryptoCC26XX_HWAttrs cryptoCC26XXHWAttrs[1] = {
    {
        .baseAddr       = CRYPTO_BASE,
        .powerMngrId    = 11, //PowerCC26XX_PERIPH_CRYPTO
        .intNum         = INT_CRYPTO_RESULT_AVAIL_IRQ,
        .intPriority    = ~0,
    }
};



const CryptoCC26XX_Config CryptoCC26XX_config[1] = {
    {
         .object  = &cryptoCC26XXObjects[0],
         .hwAttrs = &cryptoCC26XXHWAttrs[0]
    }
};
