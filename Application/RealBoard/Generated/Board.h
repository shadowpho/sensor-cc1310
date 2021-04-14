/*
 *  ======== Board.h ========
 *  Configured TI-Drivers module declarations
 *
 *  DO NOT EDIT - This file is generated for the CC1310RHB
 *  by the SysConfig tool.
 */
#ifndef Board_h
#define Board_h

#define Board_SYSCONFIG_PREVIEW

#define Board_CC1310RHB

/* Temporary define for backwards compatibility!!! */
#define __CC1310RHB_BOARD_H__

#ifndef DeviceFamily_CC13X0
#define DeviceFamily_CC13X0
#endif

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif


/*
 *  ======== ADC ========
 */

#define ADC_BatteryChannel          0
#define ADC_DCOUPL                  1
#define ADC_GROUND                  2
#define Board_DIO13_Batt            3


/*
 *  ======== GPIO ========
 */

#define Interrupt                   0
#define Sensor_Power                1

/* LEDs are active high */
#define Board_GPIO_LED_ON  (1)
#define Board_GPIO_LED_OFF (0)

#define Board_LED_ON  (Board_GPIO_LED_ON)
#define Board_LED_OFF (Board_GPIO_LED_OFF)


/*
 *  ======== I2C ========
 */

#define Board_I2C                   0

/* ======== I2C Addresses and Speeds ======== */
#include <ti/drivers/I2C.h>

/* ---- Board_I2C I2C bus components ---- */

/* no components connected to Board_I2C */

/* Board_I2C.maxBitRate configuration specified 400000 Kbps */
#define Board_I2C_MAXSPEED   (400000U) /* Kbps */
#define Board_I2C_MAXBITRATE ((I2C_BitRate)I2C_3400kHz)


/*
 *  ======== NVS ========
 */

#define Board_NVS0                  0


/*
 *  ======== PIN ========
 */

/* Includes */
#include <ti/drivers/PIN.h>

/* Externs */
extern const PIN_Config BoardGpioInitTable[];

/* Parent Signal: Board_DIO13_Batt ADC Pin, (DIO13) */
#define Board_PIN2    0x0000000d
/* Parent Signal: Interrupt GPIO Pin, (DIO0) */
#define Board_PIN5    0x00000000
/* Parent Signal: Sensor_Power GPIO Pin, (DIO3) */
#define Board_PIN7    0x00000003
/* Parent Signal: Board_I2C SDA, (DIO6) */
#define Board_PIN3    0x00000006
/* Parent Signal: Board_I2C SCL, (DIO5) */
#define Board_PIN4    0x00000005
/* Parent Signal: Board_TIMER2 PWM Pin, (DIO9) */
#define Board_PIN6    0x00000009
/* Parent Signal: Board_TIMER3 PWM Pin, (DIO10) */
#define Board_PIN8    0x0000000a
/* Parent Signal: Board_UART0 TX, (DIO1) */
#define Board_PIN0    0x00000001


/*
 *  ======== PWM ========
 */

#define LED1                        0
#define LED2                        1




/*
 *  ======== Timer ========
 */

#define Board_TIMER2                0
#define Board_TIMER3                1
#define Board_TIMER0                2


/*
 *  ======== UART ========
 */

#define Board_UART0                 0


/*
 *  ======== Watchdog ========
 */

#define Board_WATCHDOG0             0


/*
 *  ======== Board_init ========
 *  Perform all required TI-Drivers initialization
 *
 *  This function should be called once at a point before any use of
 *  TI-Drivers.
 */
extern void Board_init(void);

/*
 *  ======== Board_initGeneral ========
 *  (deprecated)
 *
 *  Board_initGeneral() is defined purely for backward compatibility.
 *
 *  All new code should use Board_init() to do any required TI-Drivers
 *  initialization _and_ use <Driver>_init() for only where specific drivers
 *  are explicitly referenced by the application.  <Driver>_init() functions
 *  are idempotent.
 */
#define Board_initGeneral Board_init

#ifdef __cplusplus
}
#endif

#endif /* include guard */
