/*
 * board_control.h
 *
 *  Created on: Apr 13, 2021
 *      Author: georg
 */

#ifndef APPLICATION_REALBOARD_BOARD_CONTROL_H_
#define APPLICATION_REALBOARD_BOARD_CONTROL_H_



#ifdef __cplusplus
extern "C"
{
#endif

void Board_Gpio_initialize();
void Board_Key_initialize();


#include <ti/drivers/crypto/CryptoCC26XX.h>


extern CryptoCC26XX_Object cryptoCC26XXObjects[1];
extern const CryptoCC26XX_HWAttrs cryptoCC26XXHWAttrs[1];
extern const CryptoCC26XX_Config CryptoCC26XX_config[1];


#ifdef __cplusplus
}
#endif



#endif /* APPLICATION_REALBOARD_BOARD_CONTROL_H_ */
