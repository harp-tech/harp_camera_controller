#include <avr/io.h>
#include "hwbp_core_types.h"
#include "app_ios_and_regs.h"

/************************************************************************/
/* Configure and initialize IOs                                         */
/************************************************************************/
void init_ios(void)
{	/* Configure input pins */
	io_pin2in(&PORTA, 0, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // CAM0_STROBE
	io_pin2in(&PORTA, 1, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // CAM0_STROBE_PU
	io_pin2in(&PORTD, 7, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // CAM1_STROBE
	io_pin2in(&PORTD, 6, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // CAM1_STROBE_PU
	io_pin2in(&PORTB, 3, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // INPUT0
	io_pin2in(&PORTD, 0, PULL_IO_TRISTATE, SENSE_IO_EDGE_RISING);        // CAM0
	io_pin2in(&PORTD, 1, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);        // OUT0
	io_pin2in(&PORTC, 0, PULL_IO_TRISTATE, SENSE_IO_EDGE_RISING);        // CAM1
	io_pin2in(&PORTC, 1, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);        // OUT1

	/* Configure input interrupts */
	io_set_int(&PORTA, INT_LEVEL_LOW, 0, (1<<0), false);                 // CAM0_STROBE
	io_set_int(&PORTA, INT_LEVEL_LOW, 0, (1<<1), false);                 // CAM0_STROBE_PU
	io_set_int(&PORTD, INT_LEVEL_LOW, 0, (1<<7), false);                 // CAM1_STROBE
	io_set_int(&PORTD, INT_LEVEL_LOW, 0, (1<<6), false);                 // CAM1_STROBE_PU
	io_set_int(&PORTB, INT_LEVEL_LOW, 1, (1<<3), false);                 // INPUT0
	io_set_int(&PORTD, INT_LEVEL_LOW, 1, (1<<0), false);                 // CAM0
	io_set_int(&PORTC, INT_LEVEL_LOW, 1, (1<<0), false);                 // CAM1

	/* Configure output pins */
	io_pin2out(&PORTA, 7, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_CAM0
	io_pin2out(&PORTC, 7, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_CAM1
	io_pin2out(&PORTR, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_STATE
	io_pin2out(&PORTD, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_PWR
	io_pin2out(&PORTA, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // EN_CAM0_TRIGGER_INV
	io_pin2out(&PORTA, 4, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // EN_CAM0_TRIGGER_N_INV
	io_pin2out(&PORTC, 4, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // EN_CAM1_TRIGGER_INV
	io_pin2out(&PORTC, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // EN_CAM1_TRIGGER_N_INV
	io_pin2out(&PORTB, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // EN_CAM0_TO_OUT0
	io_pin2out(&PORTB, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // EN_CAM1_TO_OUT1
	io_pin2out(&PORTA, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // EN_IN0_TO_CAM0
	io_pin2out(&PORTA, 6, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // EN_IN0_TO_CAM1
	io_pin2out(&PORTD, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // EN_CLOCK_IN
	io_pin2out(&PORTB, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // EN_CLOCK_OUT

	/* Initialize output pins */
	clr_LED_CAM0;
	clr_LED_CAM1;
	clr_LED_STATE;
	clr_LED_PWR;
	clr_EN_CAM0_TRIGGER_INV;
	clr_EN_CAM0_TRIGGER_N_INV;
	clr_EN_CAM1_TRIGGER_INV;
	clr_EN_CAM1_TRIGGER_N_INV;
	clr_EN_CAM0_TO_OUT0;
	clr_EN_CAM1_TO_OUT1;
	clr_EN_IN0_TO_CAM0;
	clr_EN_IN0_TO_CAM1;
	set_EN_CLOCK_IN;
	clr_EN_CLOCK_OUT;
}

/************************************************************************/
/* Registers' stuff                                                     */
/************************************************************************/
AppRegs app_regs;

uint8_t app_regs_type[] = {
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U32,
	TYPE_U32,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U16,
	TYPE_U16,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U16,
	TYPE_U16,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8
};

uint16_t app_regs_n_elements[] = {
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1
};

uint8_t *app_regs_pointer[] = {
	(uint8_t*)(&app_regs.REG_CAM0_EVENT),
	(uint8_t*)(&app_regs.REG_CAM1_EVENT),
	(uint8_t*)(&app_regs.REG_CAM0_EVENT_CONFIG),
	(uint8_t*)(&app_regs.REG_CAM1_EVENT_CONFIG),
	(uint8_t*)(&app_regs.REG_START_AND_STOP),
	(uint8_t*)(&app_regs.REG_START_TIMESTAMP),
	(uint8_t*)(&app_regs.REG_STOP_TIMESTAMP),
	(uint8_t*)(&app_regs.REG_RESERVED0),
	(uint8_t*)(&app_regs.REG_RESERVED1),
	(uint8_t*)(&app_regs.REG_CAM0_TRIGGER_CONFIG),
	(uint8_t*)(&app_regs.REG_CAM0_TRIGGER_INVERTED),
	(uint8_t*)(&app_regs.REG_CAM0_STROBE_SOURCE),
	(uint8_t*)(&app_regs.REG_CAM0_TRIGGER_FREQUENCY),
	(uint8_t*)(&app_regs.REG_CAM0_TRIGGER_DURATION_US),
	(uint8_t*)(&app_regs.REG_RESERVED2),
	(uint8_t*)(&app_regs.REG_RESERVED3),
	(uint8_t*)(&app_regs.REG_CAM1_TRIGGER_CONFIG),
	(uint8_t*)(&app_regs.REG_CAM1_TRIGGER_INVERTED),
	(uint8_t*)(&app_regs.REG_CAM1_STROBE_SOURCE),
	(uint8_t*)(&app_regs.REG_CAM1_TRIGGER_FREQUENCY),
	(uint8_t*)(&app_regs.REG_CAM1_TRIGGER_DURATION_US),
	(uint8_t*)(&app_regs.REG_RESERVED4),
	(uint8_t*)(&app_regs.REG_RESERVED5),
	(uint8_t*)(&app_regs.REG_OUT0_CONFIG),
	(uint8_t*)(&app_regs.REG_OUT1_CONFIG),
	(uint8_t*)(&app_regs.REG_RESERVED6),
	(uint8_t*)(&app_regs.REG_RESERVED7),
	(uint8_t*)(&app_regs.REG_OUT_SET),
	(uint8_t*)(&app_regs.REG_OUT_CLEAR),
	(uint8_t*)(&app_regs.REG_OUT_TOGGLE),
	(uint8_t*)(&app_regs.REG_OUT_WRITE),
	(uint8_t*)(&app_regs.REG_IN_STATE)
};