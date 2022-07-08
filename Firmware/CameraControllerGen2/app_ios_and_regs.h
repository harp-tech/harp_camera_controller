#ifndef _APP_IOS_AND_REGS_H_
#define _APP_IOS_AND_REGS_H_
#include "cpu.h"

void init_ios(void);
/************************************************************************/
/* Definition of input pins                                             */
/************************************************************************/
// CAM0_STROBE            Description: Strobe from camera 0
// CAM0_STROBE_PU         Description: Pull-up strobe from camera 0
// CAM1_STROBE            Description: Strobe from camera 1
// CAM1_STROBE_PU         Description: Pull-up strobe from camera 1
// INPUT0                 Description: Digital input 0
// CAM0                   Description: Trigger for camera 0
// OUT0                   Description: Digital output 0
// CAM1                   Description: Trigger for camera 1
// OUT1                   Description: Digital output 1

#define read_CAM0_STROBE read_io(PORTA, 0)      // CAM0_STROBE
#define read_CAM0_STROBE_PU read_io(PORTA, 1)   // CAM0_STROBE_PU
#define read_CAM1_STROBE read_io(PORTD, 7)      // CAM1_STROBE
#define read_CAM1_STROBE_PU read_io(PORTD, 6)   // CAM1_STROBE_PU
#define read_INPUT0 read_io(PORTB, 3)           // INPUT0
#define read_CAM0 read_io(PORTD, 0)             // CAM0
#define read_OUT0 read_io(PORTD, 1)             // OUT0
#define read_CAM1 read_io(PORTC, 0)             // CAM1
#define read_OUT1 read_io(PORTC, 1)             // OUT1

/************************************************************************/
/* Definition of output pins                                            */
/************************************************************************/
// LED_CAM0               Description: Camera's 0 LED
// LED_CAM1               Description: Camera's 1 LED
// LED_STATE              Description: Power's LED
// LED_PWR                Description: Power's LED
// EN_CAM0_TRIGGER_INV    Description: Enable camera's 0 direct trigger
// EN_CAM0_TRIGGER_N_INV  Description: Enable camera's 0 inverted trigger
// EN_CAM1_TRIGGER_INV    Description: Enable camera's 1 direct trigger
// EN_CAM1_TRIGGER_N_INV  Description: Enable camera's 1 inverted trigger
// EN_CAM0_TO_OUT0        Description: Connect CAM0 signal to OUT0
// EN_CAM1_TO_OUT1        Description: Connect CAM1 signal to OUT1
// EN_IN0_TO_CAM0         Description: Connect IN0 signal to CAM0
// EN_IN0_TO_CAM1         Description: Connect IN0 signal to CAM1
// EN_CLOCK_IN            Description: Digital output 1
// EN_CLOCK_OUT           Description: Digital output 1

/* LED_CAM0 */
#define set_LED_CAM0 set_io(PORTA, 7)
#define clr_LED_CAM0 clear_io(PORTA, 7)
#define tgl_LED_CAM0 toggle_io(PORTA, 7)
#define read_LED_CAM0 read_io(PORTA, 7)

/* LED_CAM1 */
#define set_LED_CAM1 set_io(PORTC, 7)
#define clr_LED_CAM1 clear_io(PORTC, 7)
#define tgl_LED_CAM1 toggle_io(PORTC, 7)
#define read_LED_CAM1 read_io(PORTC, 7)

/* LED_STATE */
#define set_LED_STATE set_io(PORTR, 0)
#define clr_LED_STATE clear_io(PORTR, 0)
#define tgl_LED_STATE toggle_io(PORTR, 0)
#define read_LED_STATE read_io(PORTR, 0)

/* LED_PWR */
#define set_LED_PWR set_io(PORTD, 5)
#define clr_LED_PWR clear_io(PORTD, 5)
#define tgl_LED_PWR toggle_io(PORTD, 5)
#define read_LED_PWR read_io(PORTD, 5)

/* EN_CAM0_TRIGGER_INV */
#define set_EN_CAM0_TRIGGER_INV clear_io(PORTA, 3)
#define clr_EN_CAM0_TRIGGER_INV set_io(PORTA, 3)
#define tgl_EN_CAM0_TRIGGER_INV toggle_io(PORTA, 3)
#define read_EN_CAM0_TRIGGER_INV read_io(PORTA, 3)

/* EN_CAM0_TRIGGER_N_INV */
#define set_EN_CAM0_TRIGGER_N_INV set_io(PORTA, 4)
#define clr_EN_CAM0_TRIGGER_N_INV clear_io(PORTA, 4)
#define tgl_EN_CAM0_TRIGGER_N_INV toggle_io(PORTA, 4)
#define read_EN_CAM0_TRIGGER_N_INV read_io(PORTA, 4)

/* EN_CAM1_TRIGGER_INV */
#define set_EN_CAM1_TRIGGER_INV clear_io(PORTC, 4)
#define clr_EN_CAM1_TRIGGER_INV set_io(PORTC, 4)
#define tgl_EN_CAM1_TRIGGER_INV toggle_io(PORTC, 4)
#define read_EN_CAM1_TRIGGER_INV read_io(PORTC, 4)

/* EN_CAM1_TRIGGER_N_INV */
#define set_EN_CAM1_TRIGGER_N_INV set_io(PORTC, 5)
#define clr_EN_CAM1_TRIGGER_N_INV clear_io(PORTC, 5)
#define tgl_EN_CAM1_TRIGGER_N_INV toggle_io(PORTC, 5)
#define read_EN_CAM1_TRIGGER_N_INV read_io(PORTC, 5)

/* EN_CAM0_TO_OUT0 */
#define set_EN_CAM0_TO_OUT0 set_io(PORTB, 0)
#define clr_EN_CAM0_TO_OUT0 clear_io(PORTB, 0)
#define tgl_EN_CAM0_TO_OUT0 toggle_io(PORTB, 0)
#define read_EN_CAM0_TO_OUT0 read_io(PORTB, 0)

/* EN_CAM1_TO_OUT1 */
#define set_EN_CAM1_TO_OUT1 set_io(PORTB, 1)
#define clr_EN_CAM1_TO_OUT1 clear_io(PORTB, 1)
#define tgl_EN_CAM1_TO_OUT1 toggle_io(PORTB, 1)
#define read_EN_CAM1_TO_OUT1 read_io(PORTB, 1)

/* EN_IN0_TO_CAM0 */
#define set_EN_IN0_TO_CAM0 set_io(PORTA, 5)
#define clr_EN_IN0_TO_CAM0 clear_io(PORTA, 5)
#define tgl_EN_IN0_TO_CAM0 toggle_io(PORTA, 5)
#define read_EN_IN0_TO_CAM0 read_io(PORTA, 5)

/* EN_IN0_TO_CAM1 */
#define set_EN_IN0_TO_CAM1 set_io(PORTA, 6)
#define clr_EN_IN0_TO_CAM1 clear_io(PORTA, 6)
#define tgl_EN_IN0_TO_CAM1 toggle_io(PORTA, 6)
#define read_EN_IN0_TO_CAM1 read_io(PORTA, 6)

/* EN_CLOCK_IN */
#define set_EN_CLOCK_IN clear_io(PORTD, 2)
#define clr_EN_CLOCK_IN set_io(PORTD, 2)
#define tgl_EN_CLOCK_IN toggle_io(PORTD, 2)
#define read_EN_CLOCK_IN read_io(PORTD, 2)

/* EN_CLOCK_OUT */
#define set_EN_CLOCK_OUT clear_io(PORTB, 2)
#define clr_EN_CLOCK_OUT set_io(PORTB, 2)
#define tgl_EN_CLOCK_OUT toggle_io(PORTB, 2)
#define read_EN_CLOCK_OUT read_io(PORTB, 2)


/************************************************************************/
/* Registers' structure                                                 */
/************************************************************************/
typedef struct
{
	uint8_t REG_CAM0_EVENT;
	uint8_t REG_CAM1_EVENT;
	uint8_t REG_CAM0_EVENT_CONFIG;
	uint8_t REG_CAM1_EVENT_CONFIG;
	uint8_t REG_START_AND_STOP;
	uint8_t REG_START_AND_STOP_TIMESTAMPED;
	uint32_t REG_START_TIMESTAMP;
	uint32_t REG_STOP_TIMESTAMP;
	uint8_t REG_RESERVED0;
	uint8_t REG_RESERVED1;
	uint8_t REG_CAM0_TRIGGER_CONFIG;
	uint8_t REG_CAM0_TRIGGER_INVERTED;
	uint8_t REG_CAM0_STROBE_SOURCE;
	uint16_t REG_CAM0_TRIGGER_FREQUENCY;
	uint16_t REG_CAM0_TRIGGER_DURATION_US;
	uint8_t REG_RESERVED2;
	uint8_t REG_RESERVED3;
	uint8_t REG_CAM1_TRIGGER_CONFIG;
	uint8_t REG_CAM1_TRIGGER_INVERTED;
	uint8_t REG_CAM1_STROBE_SOURCE;
	uint16_t REG_CAM1_TRIGGER_FREQUENCY;
	uint16_t REG_CAM1_TRIGGER_DURATION_US;
	uint8_t REG_RESERVED4;
	uint8_t REG_RESERVED5;
	uint8_t REG_OUT0_CONFIG;
	uint8_t REG_OUT1_CONFIG;
	uint8_t REG_RESERVED6;
	uint8_t REG_RESERVED7;
	uint8_t REG_OUT_SET;
	uint8_t REG_OUT_CLEAR;
	uint8_t REG_OUT_TOGGLE;
	uint8_t REG_OUT_WRITE;
	uint8_t REG_IN_STATE;
} AppRegs;

/************************************************************************/
/* Registers' address                                                   */
/************************************************************************/
/* Registers */
#define ADD_REG_CAM0_EVENT                  32 // U8     
#define ADD_REG_CAM1_EVENT                  33 // U8     
#define ADD_REG_CAM0_EVENT_CONFIG           34 // U8     
#define ADD_REG_CAM1_EVENT_CONFIG           35 // U8     
#define ADD_REG_START_AND_STOP              36 // U8     Starts and stops the cameras immediately
#define ADD_REG_START_AND_STOP_TIMESTAMPED  37 // U8     Starts and stops the cameras
#define ADD_REG_START_TIMESTAMP             38 // U32    Set when the camera starts to acquire frames
#define ADD_REG_STOP_TIMESTAMP              39 // U32    Set when the camera stops to acquire frames
#define ADD_REG_RESERVED0                   40 // U8     
#define ADD_REG_RESERVED1                   41 // U8     
#define ADD_REG_CAM0_TRIGGER_CONFIG         42 // U8     Configures the trigger source for camera 0
#define ADD_REG_CAM0_TRIGGER_INVERTED       43 // U8     Configures if trigger is inverted for camera 0
#define ADD_REG_CAM0_STROBE_SOURCE          44 // U8     Select the strobe source line for camera 0. The direct line or with pull-up
#define ADD_REG_CAM0_TRIGGER_FREQUENCY      45 // U16    Sets the trigger frequency for camera 0 between 1 and 1000
#define ADD_REG_CAM0_TRIGGER_DURATION_US    46 // U16    Sets the duration of the trigger pulse (minimum is 100) for camera 0
#define ADD_REG_RESERVED2                   47 // U8     
#define ADD_REG_RESERVED3                   48 // U8     
#define ADD_REG_CAM1_TRIGGER_CONFIG         49 // U8     Configures if trigger is inverted for camera 1
#define ADD_REG_CAM1_TRIGGER_INVERTED       50 // U8     Trigger is inverted for camera 1 in case this register is not empty (also inverts Input 0)
#define ADD_REG_CAM1_STROBE_SOURCE          51 // U8     Select the strobe source line for camera 1. The direct line or with pull-up
#define ADD_REG_CAM1_TRIGGER_FREQUENCY      52 // U16    Sets the trigger frequency for camera 1 between 1 and 1000
#define ADD_REG_CAM1_TRIGGER_DURATION_US    53 // U16    Sets the duration of the trigger pulse (minimum is 100) for camera 1
#define ADD_REG_RESERVED4                   54 // U8     
#define ADD_REG_RESERVED5                   55 // U8     
#define ADD_REG_OUT0_CONFIG                 56 // U8     Configures the digital Output 0
#define ADD_REG_OUT1_CONFIG                 57 // U8     Configures the digital Output 1
#define ADD_REG_RESERVED6                   58 // U8     
#define ADD_REG_RESERVED7                   59 // U8     
#define ADD_REG_OUT_SET                     60 // U8     Bitmask to set the digital ouputs
#define ADD_REG_OUT_CLEAR                   61 // U8     Bitmask to clear the digital ouputs
#define ADD_REG_OUT_TOGGLE                  62 // U8     Bitmask to toggle the digital ouputs
#define ADD_REG_OUT_WRITE                   63 // U8     Bitmask to write the digital ouputs
#define ADD_REG_IN_STATE                    64 // U8     Contains the state of the digital Input 0

/************************************************************************/
/* PWM Generator registers' memory limits                               */
/*                                                                      */
/* DON'T change the APP_REGS_ADD_MIN value !!!                          */
/* DON'T change these names !!!                                         */
/************************************************************************/
/* Memory limits */
#define APP_REGS_ADD_MIN                    0x20
#define APP_REGS_ADD_MAX                    0x40
#define APP_NBYTES_OF_REG_BANK              43

/************************************************************************/
/* Registers' bits                                                      */
/************************************************************************/
#define B_TRIGGER                          (1<<0)       // A trigger was detected
#define B_STROBE                           (1<<1)       // A strobe was detected
#define GM_EVENT_CONFIG                    1            // 
#define MSK_EVENT_ON_STROBE                0            // Event is sent when the strobe goes from LOW to HIGH
#define MSK_EVENT_ON_TRIGGER               1            // Event is sent when the trigger goes from LOW to HIGH
#define B_START_CAM0                       (1<<0)       // 
#define B_START_CAM1                       (1<<1)       // 
#define B_STOP_CAM0                        (1<<2)       // 
#define B_STOP_CAM1                        (1<<3)       // 
#define B_SINGLE_FRAME_CAM0                (1<<4)       // Write to this bit to trigger the camera 0 once
#define B_SINGLE_FRAME_CAM1                (1<<5)       // Write to this bit to trigger the camera 1 once
#define GM_TRG_SRC                         15           // 
#define MSK_TRG_SRC_INTERNAL               0            // Trigger is controlled by the device CAMx_TRIGGER_X registers
#define MSK_TRG_SRC_INTERNAL_RESERVED0     1            // Reserved, do not use
#define MSK_TRG_SRC_INTERNAL_1Hz           2            // Trigger is synchronously done at 1Hz
#define MSK_TRG_SRC_INTERNAL_2Hz           3            // Trigger is synchronously done at 2Hz
#define MSK_TRG_SRC_INTERNAL_5Hz           4            // Trigger is synchronously done at 5Hz
#define MSK_TRG_SRC_INTERNAL_10Hz          5            // Trigger is synchronously done at 10Hz
#define MSK_TRG_SRC_INTERNAL_RESERVED1     6            // Reserved, do not use
#define MSK_TRG_SRC_INTERNAL_20Hz          7            // Trigger is synchronously done at 20Hz
#define MSK_TRG_SRC_INTERNAL_RESERVED2     8            // Reserved, do not use
#define MSK_TRG_SRC_INTERNAL_40Hz          9            // Trigger is synchronously done at 40Hz
#define MSK_TRG_SRC_INTERNAL_50Hz          10           // Trigger is synchronously done at 50Hz
#define MSK_TRG_SRC_INTERNAL_RESERVED3     11           // Reserved, do not use
#define MSK_TRG_SRC_INTERNAL_RESERVED4     12           // Reserved, do not use
#define MSK_TRG_SRC_INTERNAL_100Hz         13           // Trigger is synchronously done at 100Hz
#define MSK_TRG_SRC_INTERNAL_125Hz         14           // Trigger is synchronously done at 125Hz
#define MSK_TRG_SRC_INPUT0                 15           // Trigger is controlled by the external Input 0
#define GM_TRIGGER_INVERTED                1            // 
#define MSK_TRIGGER_INVERTED_NO            0            // Selects the direct line
#define MSK_TRIGGER_INVERTED_YES           1            // Selects the pull-up line
#define GM_STROBE_SOURCE                   1            // 
#define MSK_STROBE_DIRECT                  0            // Selects the direct line
#define MSK_STROBE_PULL_UP                 1            // Selects the pull-up line
#define GM_OUT0_CONFIG                     3            // 
#define MSK_OUT0_SOFTWARE                  0            // Output 0 is exclusively controlled by comands
#define MSK_OUT0_TRIGGER_CAM0              1            // Output 0 follows the trigger of camera 0 (not inverted)
#define MSK_OUT0_STROBE_CAM0               2            // Output 0 follows the strobe of camera 0
#define GM_OUT1_CONFIG                     3            // 
#define MSK_OUT1_SOFTWARE                  0            // Output 1 is exclusively controlled by comands
#define MSK_OUT1_TRIGGER_CAM1              1            // Output 1 follows the trigger of camera 1 (not inverted)
#define MSK_OUT1_STROBE_CAM1               2            // Output 1 follows the strobe of camera 1
#define B_OUT0                             (1<<0)       // 
#define B_OUT1                             (1<<1)       // 
#define B_IN0                              (1<<0)       // 

#endif /* _APP_REGS_H_ */