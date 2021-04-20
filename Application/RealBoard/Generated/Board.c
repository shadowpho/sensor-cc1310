/*
 *  ======== Board.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the CC1310RHB
 *  by the SysConfig tool.
 */

#include <stddef.h>

#ifndef DeviceFamily_CC13X0
#define DeviceFamily_CC13X0
#endif

#include <ti/devices/DeviceFamily.h>

#include "Board.h"

/*
 *  =============================== ADC ===============================
 */

#include <ti/drivers/ADC.h>
#include <ti/drivers/adc/ADCCC26XX.h>

#define Board_ADCCOUNT 4

/*
 *  ======== adcCC26xxObjects ========
 */
ADCCC26XX_Object adcCC26xxObjects[Board_ADCCOUNT];

/*
 *  ======== adcCC26xxHWAttrs ========
 */
const ADCCC26XX_HWAttrs adcCC26xxHWAttrs[Board_ADCCOUNT] = {
    /* ADC_BatteryChannel */
    {
        .adcDIO              = PIN_UNASSIGNED,
        .adcCompBInput       = ADC_COMPB_IN_VDDS,
        .refSource           = ADCCC26XX_FIXED_REFERENCE,
        .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
        .inputScalingEnabled = true,
        .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,
        .returnAdjustedVal   = true
    },
    /* ADC_DCOUPL */
    {
        .adcDIO              = PIN_UNASSIGNED,
        .adcCompBInput       = ADC_COMPB_IN_DCOUPL,
        .refSource           = ADCCC26XX_FIXED_REFERENCE,
        .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
        .inputScalingEnabled = true,
        .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,
        .returnAdjustedVal   = true
    },
    /* ADC_GROUND */
    {
        .adcDIO              = PIN_UNASSIGNED,
        .adcCompBInput       = ADC_COMPB_IN_VSS,
        .refSource           = ADCCC26XX_FIXED_REFERENCE,
        .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
        .inputScalingEnabled = true,
        .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,
        .returnAdjustedVal   = false
    },
    /* Board_DIO13_Batt */
    {
        .adcDIO              = IOID_13,
        .adcCompBInput       = ADC_COMPB_IN_AUXIO1,
        .refSource           = ADCCC26XX_FIXED_REFERENCE,
        .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
        .inputScalingEnabled = true,
        .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,
        .returnAdjustedVal   = true
    },
};

/*
 *  ======== ADC_config ========
 */
const ADC_Config ADC_config[Board_ADCCOUNT] = {
    /* ADC_BatteryChannel */
    {
        .fxnTablePtr = &ADCCC26XX_fxnTable,
        .object = &adcCC26xxObjects[ADC_BatteryChannel],
        .hwAttrs = &adcCC26xxHWAttrs[ADC_BatteryChannel]
    },
    /* ADC_DCOUPL */
    {
        .fxnTablePtr = &ADCCC26XX_fxnTable,
        .object = &adcCC26xxObjects[ADC_DCOUPL],
        .hwAttrs = &adcCC26xxHWAttrs[ADC_DCOUPL]
    },
    /* ADC_GROUND */
    {
        .fxnTablePtr = &ADCCC26XX_fxnTable,
        .object = &adcCC26xxObjects[ADC_GROUND],
        .hwAttrs = &adcCC26xxHWAttrs[ADC_GROUND]
    },
    /* Board_DIO13_Batt */
    {
        .fxnTablePtr = &ADCCC26XX_fxnTable,
        .object = &adcCC26xxObjects[Board_DIO13_Batt],
        .hwAttrs = &adcCC26xxHWAttrs[Board_DIO13_Batt]
    },
};

const uint_least8_t ADC_count = Board_ADCCOUNT;


/*
 *  =============================== GPIO ===============================
 */

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOCC26XX.h>

/*
 *  ======== gpioPinConfigs ========
 *  Array of Pin configurations
 */
GPIO_PinConfig gpioPinConfigs[] = {
    /* Interrupt */
    GPIOCC26XX_DIO_00 | GPIO_CFG_IN_PD | GPIO_CFG_IN_INT_NONE,
    /* Sensor_Power */
    GPIOCC26XX_DIO_03 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,
};

/*
 *  ======== GPIOCC26XX_config ========
 */
const GPIOCC26XX_Config GPIOCC26XX_config = {
    .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = NULL,
    .numberOfPinConfigs = 2,
    .numberOfCallbacks = 0,
    .intPriority = (~0)
};


/*
 *  =============================== I2C ===============================
 */

#include <ti/drivers/I2C.h>
#include <ti/drivers/i2c/I2CCC26XX.h>
#include <ti/drivers/power/PowerCC26XX.h>

#define Board_I2CCOUNT 1

/*
 *  ======== i2cCC26xxObjects ========
 */
I2CCC26XX_Object i2cCC26xxObjects[Board_I2CCOUNT];

/*
 *  ======== i2cCC26xxHWAttrs ========
 */
const I2CCC26XX_HWAttrsV1 i2cCC26xxHWAttrs[Board_I2CCOUNT] = {
    /* Board_I2C */
    {
        .baseAddr    = I2C0_BASE,
        .powerMngrId = PowerCC26XX_PERIPH_I2C0,
        .intNum      = INT_I2C_IRQ,
        .intPriority = (~0),
        .swiPriority = 0,
        .sclPin      = IOID_5,
        .sdaPin      = IOID_6
    },
};

/*
 *  ======== I2C_config ========
 */
const I2C_Config I2C_config[Board_I2CCOUNT] = {
    /* Board_I2C */
    {
        .fxnTablePtr = &I2CCC26XX_fxnTable,
        .object      = &i2cCC26xxObjects[Board_I2C],
        .hwAttrs     = &i2cCC26xxHWAttrs[Board_I2C]
    },
};

const uint_least8_t I2C_count = Board_I2CCOUNT;


/*
 *  =============================== NVS ===============================
 */

#include <ti/drivers/NVS.h>
#include <ti/drivers/nvs/NVSCC26XX.h>

/*
 *  NVSCC26XX Internal NVS flash region definitions
 */

/*
 * Place uninitialized 'flashBuf' char arrays at addresses
 * corresponding to the 'regionBase' addresses defined in
 * the configured NVS regions. These arrays are used as
 * place holders so that the linker will not place other
 * content there.
 *
 * For GCC targets, the 'flashBuf' arrays are each placed into
 * the shared ".nvs" section. The user must add content to
 * their GCC linker command file to place the .nvs section
 * at the lowest 'regionbase' address specified in their NVS
 * regions.
 */

#if defined(__TI_COMPILER_VERSION__)

#pragma LOCATION(flashBuf0, 0x0);
#pragma NOINIT(flashBuf0);
static char flashBuf0[0x1000];

#elif defined(__IAR_SYSTEMS_ICC__)

__no_init static char flashBuf0[0x1000] @ 0x0;

#elif defined(__GNUC__)

__attribute__ ((section (".nvs")))
static char flashBuf0[0x1000];

#endif

NVSCC26XX_Object nvsCC26XXObjects[1];

static const NVSCC26XX_HWAttrs nvsCC26XXHWAttrs[1] = {
    /* Board_NVS0 */
    {
        .regionBase = flashBuf0,
        .regionSize = 0x1000
    },
};

#define Board_NVSCOUNT 1

const NVS_Config NVS_config[Board_NVSCOUNT] = {
    /* Board_NVS0 */
    {
        .fxnTablePtr = &NVSCC26XX_fxnTable,
        .object = &nvsCC26XXObjects[0],
        .hwAttrs = &nvsCC26XXHWAttrs[0],
    },
};

const uint_least8_t NVS_count = Board_NVSCOUNT;


/*
 *  =============================== PIN ===============================
 */

#include <ti/drivers/PIN.h>
#include <ti/drivers/pin/PINCC26XX.h>

const PIN_Config BoardGpioInitTable[] = {
    /* Parent Signal: Board_DIO13_Batt ADC Pin, (DIO13) */
    Board_PIN2 | PIN_INPUT_EN | PIN_NOPULL | PIN_IRQ_DIS | PIN_HYSTERESIS,
    /* Parent Signal: Interrupt GPIO Pin, (DIO0) */
    Board_PIN5 | PIN_INPUT_EN | PIN_PULLDOWN | PIN_IRQ_DIS,
    /* Parent Signal: Sensor_Power GPIO Pin, (DIO3) */
    Board_PIN7 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    /* Parent Signal: Board_I2C SDA, (DIO6) */
    Board_PIN3 | PIN_INPUT_EN | PIN_PULLDOWN | PIN_IRQ_DIS,
    /* Parent Signal: Board_I2C SCL, (DIO5) */
    Board_PIN4 | PIN_INPUT_EN | PIN_PULLDOWN | PIN_IRQ_DIS,
    /* Parent Signal: Board_TIMER2 PWM Pin, (DIO9) */
    Board_PIN6 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_DIS,
    /* Parent Signal: Board_TIMER3 PWM Pin, (DIO10) */
    Board_PIN8 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_DIS,
    /* Parent Signal: Board_UART0 TX, (DIO1) */
    Board_PIN0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MED,

    PIN_TERMINATE
};

const PINCC26XX_HWAttrs PINCC26XX_hwAttrs = {
    .intPriority = (~0),
    .swiPriority = 0
};


/*
 *  =============================== PWM ===============================
 */

#include <ti/drivers/PWM.h>
#include <ti/drivers/pwm/PWMTimerCC26XX.h>

/* include driverlib definitions */
#include <ti/devices/cc13x0/driverlib/ioc.h>
#include <ti/devices/cc13x0/inc/hw_ints.h>
#include <ti/devices/cc13x0/inc/hw_memmap.h>

#define Board_PWMCOUNT 2

/*
 *  ======== pwmCC26XXObjects ========
 */
PWMTimerCC26XX_Object pwmTimerCC26XXObjects[Board_PWMCOUNT];

/*
 *  ======== pwmCC26XXHWAttrs ========
 */
const PWMTimerCC26XX_HwAttrs pwmTimerCC26XXHWAttrs[Board_PWMCOUNT] = {
    /* LED1 */
    {
        .pwmPin = IOID_9,
        .gpTimerUnit = Board_TIMER2
    },
    /* LED2 */
    {
        .pwmPin = IOID_10,
        .gpTimerUnit = Board_TIMER3
    },
};

/*
 *  ======== PWM_config ========
 */
const PWM_Config PWM_config[Board_PWMCOUNT] = {
    /* LED1 */
    {
        .fxnTablePtr = &PWMTimerCC26XX_fxnTable,
        .object = &pwmTimerCC26XXObjects[LED1],
        .hwAttrs = &pwmTimerCC26XXHWAttrs[LED1]
    },
    /* LED2 */
    {
        .fxnTablePtr = &PWMTimerCC26XX_fxnTable,
        .object = &pwmTimerCC26XXObjects[LED2],
        .hwAttrs = &pwmTimerCC26XXHWAttrs[LED2]
    },
};

const uint_least8_t PWM_count = Board_PWMCOUNT;


/*
 *  =============================== Power ===============================
 */
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26XX.h>
#include "Board.h"

extern void PowerCC26XX_standbyPolicy(void);
extern bool PowerCC26XX_calibrate(unsigned int);

const PowerCC26XX_Config PowerCC26XX_config = {
    .enablePolicy             = true,
    .policyInitFxn            = NULL,
    .policyFxn                = PowerCC26XX_standbyPolicy,
    .calibrateFxn             = PowerCC26XX_calibrate,
    .vddrRechargeMargin       = 0,
    .calibrateRCOSC_LF        = true,
    .calibrateRCOSC_HF        = true,
};


/*
 *  =============================== RF Driver ===============================
 */

#include <ti/drivers/rf/RF.h>

const RFCC26XX_HWAttrsV2 RFCC26XX_hwAttrs = {
    .hwiPriority        = (~0),
    .swiPriority        = (uint8_t)0,
    .xoscHfAlwaysNeeded = false,
    .globalCallback     = NULL,
    .globalEventMask    = 0
};


/*
 *  =============================== GPTimer ===============================
 */

#include <ti/drivers/timer/GPTimerCC26XX.h>
#include <ti/drivers/power/PowerCC26XX.h>
#include <ti/devices/cc13x0/inc/hw_memmap.h>
#include <ti/devices/cc13x0/inc/hw_ints.h>

#define Board_TIMERCOUNT 3

/*
 *  ======== timerCC26XXObjects ========
 */
GPTimerCC26XX_Object timerCC26XXObjects[Board_TIMERCOUNT];

/*
 *  ======== timerCC26XXHWAttrs ========
 */
const GPTimerCC26XX_HWAttrs timerCC26XXHWAttrs[Board_TIMERCOUNT] = {
    /* Board_TIMER2, used by LED1 */
    {
        .baseAddr = GPT1_BASE,
        .intNum      = INT_GPT1A,
        .intPriority = (~0),
        .powerMngrId = PowerCC26XX_PERIPH_GPT1,
        .pinMux      = GPT_PIN_1A
    },
    /* Board_TIMER3, used by LED2 */
    {
        .baseAddr = GPT1_BASE,
        .intNum      = INT_GPT1B,
        .intPriority = (~0),
        .powerMngrId = PowerCC26XX_PERIPH_GPT1,
        .pinMux      = GPT_PIN_1B
    },
    /* Board_TIMER0 */
    {
        .baseAddr = GPT0_BASE,
        .intNum      = INT_GPT0A,
        .intPriority = (~0),
        .powerMngrId = PowerCC26XX_PERIPH_GPT0,
        .pinMux      = GPT_PIN_0A
    },
};

/*
 *  ======== Timer_config ========
 */
const GPTimerCC26XX_Config GPTimerCC26XX_config[Board_TIMERCOUNT] = {
    /* Board_TIMER2 */
    {
        .object    = &timerCC26XXObjects[Board_TIMER2],
        .hwAttrs   = &timerCC26XXHWAttrs[Board_TIMER2],
        .timerPart = GPT_A
    },
    /* Board_TIMER3 */
    {
        .object    = &timerCC26XXObjects[Board_TIMER3],
        .hwAttrs   = &timerCC26XXHWAttrs[Board_TIMER3],
        .timerPart = GPT_B
    },
    /* Board_TIMER0 */
    {
        .object    = &timerCC26XXObjects[Board_TIMER0],
        .hwAttrs   = &timerCC26XXHWAttrs[Board_TIMER0],
        .timerPart = GPT_A
    },
};

const uint_least8_t Timer_count = Board_TIMERCOUNT;


/*
 *  =============================== UART ===============================
 */

#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTCC26XX.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26XX.h>
#include <ti/devices/cc13x0/inc/hw_memmap.h>
#include <ti/devices/cc13x0/inc/hw_ints.h>

#define Board_UARTCOUNT 1

UARTCC26XX_Object uartCC26XXObjects[Board_UARTCOUNT];

static unsigned char uartCC26XXRingBuffer0[128];

static const UARTCC26XX_HWAttrsV2 uartCC26XXHWAttrs[Board_UARTCOUNT] = {
  {
    .baseAddr           = UART0_BASE,
    .intNum             = INT_UART0_COMB,
    .intPriority        = (~0),
    .swiPriority        = 0,
    .powerMngrId        = PowerCC26XX_PERIPH_UART0,
    .ringBufPtr         = uartCC26XXRingBuffer0,
    .ringBufSize        = sizeof(uartCC26XXRingBuffer0),
    .rxPin              = PIN_UNASSIGNED,
    .txPin              = IOID_1,
    .ctsPin             = PIN_UNASSIGNED,
    .rtsPin             = PIN_UNASSIGNED,
    .txIntFifoThr       = UARTCC26XX_FIFO_THRESHOLD_1_8,
    .rxIntFifoThr       = UARTCC26XX_FIFO_THRESHOLD_4_8,
    .errorFxn           = NULL
  },
};

const UART_Config UART_config[Board_UARTCOUNT] = {
    {   /* Board_UART0 */
        .fxnTablePtr = &UARTCC26XX_fxnTable,
        .object      = &uartCC26XXObjects[0],
        .hwAttrs     = &uartCC26XXHWAttrs[0]
    },
};

const uint_least8_t UART_count = Board_UARTCOUNT;


/*
 *  =============================== Watchdog ===============================
 */

#include <ti/drivers/Watchdog.h>
#include <ti/drivers/watchdog/WatchdogCC26XX.h>
#include <ti/devices/cc13x0/inc/hw_memmap.h>

#define Board_WATCHDOGCOUNT 1

WatchdogCC26XX_Object watchdogCC26XXObjects[Board_WATCHDOGCOUNT];

const WatchdogCC26XX_HWAttrs watchdogCC26XXHWAttrs[Board_WATCHDOGCOUNT] = {
    /* Board_WATCHDOG0: period = 10000 */
    {
        .baseAddr    = WDT_BASE,
        .reloadValue = 10000
    },
};

const Watchdog_Config Watchdog_config[Board_WATCHDOGCOUNT] = {
    /* Board_WATCHDOG0 */
    {
        .fxnTablePtr = &WatchdogCC26XX_fxnTable,
        .object      = &watchdogCC26XXObjects[Board_WATCHDOG0],
        .hwAttrs     = &watchdogCC26XXHWAttrs[Board_WATCHDOG0]
    }
};

const uint_least8_t Watchdog_count = Board_WATCHDOGCOUNT;


#include <ti/drivers/Board.h>

/*
 *  ======== Board_initHook ========
 *  Perform any board-specific initialization needed at startup.  This
 *  function is declared weak to allow applications to override it if needed.
 */
#if defined(__IAR_SYSTEMS_ICC__)
__weak void Board_initHook(void)
#elif defined(__GNUC__) && !defined(__ti__)
void __attribute__((weak)) Board_initHook(void)
#else
#pragma WEAK (Board_initHook)
void Board_initHook(void)
#endif
{
}

/*
 *  ======== Board_init ========
 *  Perform any initialization needed before using any board APIs
 */
void Board_init(void)
{
    /* ==== /ti/drivers/Power initialization ==== */
    Power_init();

    /* ==== /ti/drivers/PIN initialization ==== */
    if (PIN_init(BoardGpioInitTable) != PIN_SUCCESS) {
        /* Error with PIN_init */
        while (1);
    }

    Board_initHook();
}
