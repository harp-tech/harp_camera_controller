#include "app_funcs.h"
#include "app_ios_and_regs.h"
#include "hwbp_core.h"

#define F_CPU 32000000
#include <util/delay.h>


/************************************************************************/
/* Create pointers to functions                                         */
/************************************************************************/
extern AppRegs app_regs;

void (*app_func_rd_pointer[])(void) = {
	&app_read_REG_CAM0_EVENT,
	&app_read_REG_CAM1_EVENT,
	&app_read_REG_CAM0_EVENT_CONFIG,
	&app_read_REG_CAM1_EVENT_CONFIG,
	&app_read_REG_START_AND_STOP,
	&app_read_REG_START_AND_STOP_TIMESTAMPED,
	&app_read_REG_START_TIMESTAMP,
	&app_read_REG_STOP_TIMESTAMP,	
	&app_read_REG_RESERVED0,
	&app_read_REG_RESERVED1,
	&app_read_REG_CAM0_TRIGGER_CONFIG,
	&app_read_REG_CAM0_TRIGGER_INVERTED,
	&app_read_REG_CAM0_STROBE_SOURCE,
	&app_read_REG_CAM0_TRIGGER_FREQUENCY,
	&app_read_REG_CAM0_TRIGGER_DURATION_US,
	&app_read_REG_RESERVED2,
	&app_read_REG_RESERVED3,
	&app_read_REG_CAM1_TRIGGER_CONFIG,
	&app_read_REG_CAM1_TRIGGER_INVERTED,
	&app_read_REG_CAM1_STROBE_SOURCE,
	&app_read_REG_CAM1_TRIGGER_FREQUENCY,
	&app_read_REG_CAM1_TRIGGER_DURATION_US,
	&app_read_REG_RESERVED4,
	&app_read_REG_RESERVED5,
	&app_read_REG_OUT0_CONFIG,
	&app_read_REG_OUT1_CONFIG,
	&app_read_REG_RESERVED6,
	&app_read_REG_RESERVED7,
	&app_read_REG_OUT_SET,
	&app_read_REG_OUT_CLEAR,
	&app_read_REG_OUT_TOGGLE,
	&app_read_REG_OUT_WRITE,
	&app_read_REG_IN_STATE
};

bool (*app_func_wr_pointer[])(void*) = {
	&app_write_REG_CAM0_EVENT,
	&app_write_REG_CAM1_EVENT,
	&app_write_REG_CAM0_EVENT_CONFIG,
	&app_write_REG_CAM1_EVENT_CONFIG,
	&app_write_REG_START_AND_STOP,
	&app_write_REG_START_AND_STOP_TIMESTAMPED,
	&app_write_REG_START_TIMESTAMP,
	&app_write_REG_STOP_TIMESTAMP,
	&app_write_REG_RESERVED0,
	&app_write_REG_RESERVED1,
	&app_write_REG_CAM0_TRIGGER_CONFIG,
	&app_write_REG_CAM0_TRIGGER_INVERTED,
	&app_write_REG_CAM0_STROBE_SOURCE,
	&app_write_REG_CAM0_TRIGGER_FREQUENCY,
	&app_write_REG_CAM0_TRIGGER_DURATION_US,
	&app_write_REG_RESERVED2,
	&app_write_REG_RESERVED3,
	&app_write_REG_CAM1_TRIGGER_CONFIG,
	&app_write_REG_CAM1_TRIGGER_INVERTED,
	&app_write_REG_CAM1_STROBE_SOURCE,
	&app_write_REG_CAM1_TRIGGER_FREQUENCY,
	&app_write_REG_CAM1_TRIGGER_DURATION_US,
	&app_write_REG_RESERVED4,
	&app_write_REG_RESERVED5,
	&app_write_REG_OUT0_CONFIG,
	&app_write_REG_OUT1_CONFIG,
	&app_write_REG_RESERVED6,
	&app_write_REG_RESERVED7,
	&app_write_REG_OUT_SET,
	&app_write_REG_OUT_CLEAR,
	&app_write_REG_OUT_TOGGLE,
	&app_write_REG_OUT_WRITE,
	&app_write_REG_IN_STATE
};


/************************************************************************/
/* REG_CAM0_EVENT                                                       */
/************************************************************************/
void app_read_REG_CAM0_EVENT(void) {}
bool app_write_REG_CAM0_EVENT(void *a) { return false; }


/************************************************************************/
/* REG_CAM1_EVENT                                                       */
/************************************************************************/
void app_read_REG_CAM1_EVENT(void) {}
bool app_write_REG_CAM1_EVENT(void *a) { return false; }


/************************************************************************/
/* REG_CAM0_EVENT_CONFIG                                                */
/************************************************************************/
void app_read_REG_CAM0_EVENT_CONFIG(void) {}
bool app_write_REG_CAM0_EVENT_CONFIG(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (reg & ~GM_EVENT_CONFIG)
		return false;

	app_regs.REG_CAM0_EVENT_CONFIG = reg;
	return true;
}


/************************************************************************/
/* REG_CAM1_EVENT_CONFIG                                                */
/************************************************************************/
void app_read_REG_CAM1_EVENT_CONFIG(void) {}
bool app_write_REG_CAM1_EVENT_CONFIG(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (reg & ~GM_EVENT_CONFIG)
		return false;

	app_regs.REG_CAM1_EVENT_CONFIG = reg;
	return true;
}


/************************************************************************/
/* REG_START_AND_STOP                                                   */
/************************************************************************/
bool cam0_start_request = false;
bool cam1_start_request = false;
bool cam0_stop_request = false;
bool cam1_stop_request = false;
bool cam0_acquiring = false;
bool cam1_acquiring = false;

extern bool stop_cam0_when_possible;
extern bool stop_cam1_when_possible;

uint8_t cam0_freq_prescaler;
uint8_t cam1_freq_prescaler;
uint16_t cam0_freq_target_count;
uint16_t cam1_freq_target_count;
uint16_t cam0_freq_dutycyle;
uint16_t cam1_freq_dutycyle;

uint8_t cam0_pulse_prescaler;
uint8_t cam1_pulse_prescaler;
uint16_t cam0_pulse_target_count;
uint16_t cam1_pulse_target_count;

void app_read_REG_START_AND_STOP(void)
{
	app_regs.REG_START_AND_STOP  = (cam0_acquiring) ? B_START_CAM0 : B_STOP_CAM0;
	app_regs.REG_START_AND_STOP |= (cam1_acquiring) ? B_START_CAM1 : B_STOP_CAM1;
}

bool app_write_REG_START_AND_STOP(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (reg & B_START_CAM0)
		if (app_regs.REG_CAM0_TRIGGER_CONFIG != MSK_TRG_SRC_INPUT0)
			if (cam0_acquiring == false)
				cam0_start_request = true;
	
	if (reg & B_START_CAM1)
		if (app_regs.REG_CAM1_TRIGGER_CONFIG != MSK_TRG_SRC_INPUT0)
			if (cam1_acquiring == false)
				cam1_start_request = true;
				
	if (reg & B_STOP_CAM0)
		if (app_regs.REG_CAM0_TRIGGER_CONFIG != MSK_TRG_SRC_INPUT0)
		{
			if (cam0_start_request) cam0_start_request = false;
			if (cam0_acquiring)     cam0_stop_request = true;
		}
				
	if (reg & B_STOP_CAM1)
		if (app_regs.REG_CAM1_TRIGGER_CONFIG != MSK_TRG_SRC_INPUT0)
		{
			if (cam1_start_request) cam1_start_request = false;
			if (cam1_acquiring)     cam1_stop_request = true;
		}
		
	if (reg & B_SINGLE_FRAME_CAM0)
		if (app_regs.REG_CAM0_TRIGGER_CONFIG != MSK_TRG_SRC_INPUT0)
		{
			if (cam0_acquiring)     return false;
			if (cam0_start_request)	return false;
			
			timer_type0_pwm(&TCD0, cam0_freq_prescaler, cam0_freq_target_count, cam0_freq_dutycyle, INT_LEVEL_LOW, INT_LEVEL_LOW);
			stop_cam0_when_possible = true;
		}
	
	if (reg & B_SINGLE_FRAME_CAM1)
		if (app_regs.REG_CAM1_TRIGGER_CONFIG != MSK_TRG_SRC_INPUT0)
		{
			if (cam1_acquiring)     return false;
			if (cam1_start_request)	return false;
			
			timer_type0_pwm(&TCC0, cam1_freq_prescaler, cam1_freq_target_count, cam1_freq_dutycyle, INT_LEVEL_LOW, INT_LEVEL_LOW);
			stop_cam1_when_possible = true;
		}			

	app_regs.REG_START_AND_STOP = reg;
	return true;
}


/************************************************************************/
/* REG_START_AND_STOP_TIMESTAMPED                                       */
/************************************************************************/
void app_read_REG_START_AND_STOP_TIMESTAMPED(void)
{
	
}

bool app_write_REG_START_AND_STOP_TIMESTAMPED(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_START_AND_STOP_TIMESTAMPED = reg;
	return true;
}


/************************************************************************/
/* REG_START_TIMESTAMP                                                  */
/************************************************************************/
void app_read_REG_START_TIMESTAMP(void) {}
bool app_write_REG_START_TIMESTAMP(void *a)
{
	uint32_t reg = *((uint32_t*)a);

	app_regs.REG_START_TIMESTAMP = reg;
	return true;
}


/************************************************************************/
/* REG_STOP_TIMESTAMP                                                   */
/************************************************************************/
void app_read_REG_STOP_TIMESTAMP(void) {}
bool app_write_REG_STOP_TIMESTAMP(void *a)
{
	uint32_t reg = *((uint32_t*)a);

	app_regs.REG_STOP_TIMESTAMP = reg;
	return true;
}


/************************************************************************/
/* REG_RESERVED0                                                        */
/************************************************************************/
void app_read_REG_RESERVED0(void) {}
bool app_write_REG_RESERVED0(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_RESERVED0 = reg;
	return true;
}


/************************************************************************/
/* REG_RESERVED1                                                        */
/************************************************************************/
void app_read_REG_RESERVED1(void) {}
bool app_write_REG_RESERVED1(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_RESERVED1 = reg;
	return true;
}


/************************************************************************/
/* REG_CAM0_TRIGGER_CONFIG                                              */
/************************************************************************/
void app_read_REG_CAM0_TRIGGER_CONFIG(void) {}
bool app_write_REG_CAM0_TRIGGER_CONFIG(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (cam0_acquiring)     return false;
	if (cam0_start_request)	return false;
	
	if (reg & ~GM_TRG_SRC)
		return false;
	else
	{
		switch (reg)
		{
			case MSK_TRG_SRC_INPUT0:
						
				io_pin2in(&PORTD, 0, PULL_IO_TRISTATE, SENSE_IO_EDGE_RISING);	// CAM0 to input
				_delay_us(10);
				set_EN_IN0_TO_CAM0;
				break;
			
			default:
			
				clr_EN_IN0_TO_CAM0;
				_delay_us(10);
				io_pin2out(&PORTD, 0, OUT_IO_DIGITAL, IN_EN_IO_DIS);			// CAM0
		}
	}

	app_regs.REG_CAM0_TRIGGER_CONFIG = reg;
	return true;
}


/************************************************************************/
/* REG_CAM0_TRIGGER_INVERTED                                            */
/************************************************************************/
void app_read_REG_CAM0_TRIGGER_INVERTED(void) {}
bool app_write_REG_CAM0_TRIGGER_INVERTED(void *a)
{
	uint8_t reg = *((uint8_t*)a);	
	
	if (reg & ~GM_TRIGGER_INVERTED)
		return false;
	
	switch (reg)
	{
		case MSK_TRIGGER_INVERTED_NO:
		
			clr_EN_CAM0_TRIGGER_INV;
			_delay_us(10);
			set_EN_CAM0_TRIGGER_N_INV;
			break;
			
		case MSK_TRIGGER_INVERTED_YES:
		
			clr_EN_CAM0_TRIGGER_N_INV;
			_delay_us(10);		
			set_EN_CAM0_TRIGGER_INV;
			break;
	}		

	app_regs.REG_CAM0_TRIGGER_INVERTED = reg;
	return true;
}


/************************************************************************/
/* REG_CAM0_STROBE_ORIGIN                                               */
/************************************************************************/
void app_read_REG_CAM0_STROBE_SOURCE(void) {}
bool app_write_REG_CAM0_STROBE_SOURCE(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (reg & ~GM_STROBE_SOURCE)
		return false;
		
	switch (reg)
	{
		case MSK_STROBE_DIRECT:
			io_set_int(&PORTA, INT_LEVEL_LOW, 0, (1<<0), true);	// Sets CAM0_STROBE as the interrupt source
			break;
		
		case MSK_STROBE_PULL_UP:
			io_set_int(&PORTA, INT_LEVEL_LOW, 0, (1<<1), true);	// Sets CAM0_STROBE_PU as the interrupt source
			break;
	}
	
	app_regs.REG_CAM0_STROBE_SOURCE = reg;
	return true;
}


/************************************************************************/
/* REG_CAM0_TRIGGER_FREQUENCY                                           */
/************************************************************************/
void update_cam0_timer_pre_values(void)
{
	calculate_timer_16bits(32000000, app_regs.REG_CAM0_TRIGGER_FREQUENCY, &cam0_freq_prescaler, &cam0_freq_target_count);
	calculate_timer_16bits(32000000, 1000000.0/app_regs.REG_CAM0_TRIGGER_DURATION_US, &cam0_pulse_prescaler, &cam0_pulse_target_count);
	
	switch (cam0_freq_prescaler)
	{
		case TIMER_PRESCALER_DIV1:    cam0_freq_dutycyle = (app_regs.REG_CAM0_TRIGGER_DURATION_US *32.0) / 1.0;    return;
		case TIMER_PRESCALER_DIV2:    cam0_freq_dutycyle = (app_regs.REG_CAM0_TRIGGER_DURATION_US *32.0) / 2.0;    return;
		case TIMER_PRESCALER_DIV4:    cam0_freq_dutycyle = (app_regs.REG_CAM0_TRIGGER_DURATION_US *32.0) / 4.0;    return;
		case TIMER_PRESCALER_DIV8:    cam0_freq_dutycyle = (app_regs.REG_CAM0_TRIGGER_DURATION_US *32.0) / 8.0;    return;
		case TIMER_PRESCALER_DIV64:   cam0_freq_dutycyle = (app_regs.REG_CAM0_TRIGGER_DURATION_US *32.0) / 64.0;   return;
		case TIMER_PRESCALER_DIV256:  cam0_freq_dutycyle = (app_regs.REG_CAM0_TRIGGER_DURATION_US *32.0) / 256.0;  return;
		case TIMER_PRESCALER_DIV1024: cam0_freq_dutycyle = (app_regs.REG_CAM0_TRIGGER_DURATION_US *32.0) / 1024.0; return;
	}	
}

void update_cam1_timer_pre_values(void)
{
	calculate_timer_16bits(32000000, app_regs.REG_CAM1_TRIGGER_FREQUENCY, &cam1_freq_prescaler, &cam1_freq_target_count);
	calculate_timer_16bits(32000000, 1000000.0/app_regs.REG_CAM1_TRIGGER_DURATION_US, &cam1_pulse_prescaler, &cam1_pulse_target_count);
	
	switch (cam1_freq_prescaler)
	{
		case TIMER_PRESCALER_DIV1:    cam1_freq_dutycyle = (app_regs.REG_CAM1_TRIGGER_DURATION_US *32.0) / 1.0;    return;
		case TIMER_PRESCALER_DIV2:    cam1_freq_dutycyle = (app_regs.REG_CAM1_TRIGGER_DURATION_US *32.0) / 2.0;    return;
		case TIMER_PRESCALER_DIV4:    cam1_freq_dutycyle = (app_regs.REG_CAM1_TRIGGER_DURATION_US *32.0) / 4.0;    return;
		case TIMER_PRESCALER_DIV8:    cam1_freq_dutycyle = (app_regs.REG_CAM1_TRIGGER_DURATION_US *32.0) / 8.0;    return;
		case TIMER_PRESCALER_DIV64:   cam1_freq_dutycyle = (app_regs.REG_CAM1_TRIGGER_DURATION_US *32.0) / 64.0;   return;
		case TIMER_PRESCALER_DIV256:  cam1_freq_dutycyle = (app_regs.REG_CAM1_TRIGGER_DURATION_US *32.0) / 256.0;  return;
		case TIMER_PRESCALER_DIV1024: cam1_freq_dutycyle = (app_regs.REG_CAM1_TRIGGER_DURATION_US *32.0) / 1024.0; return;
	}
}

void app_read_REG_CAM0_TRIGGER_FREQUENCY(void) {}
bool app_write_REG_CAM0_TRIGGER_FREQUENCY(void *a)
{
	uint16_t reg = *((uint16_t*)a);
	
	if (reg < 1 || reg > 1000)
		return false;
	
	if (cam0_acquiring)
		return false;

	app_regs.REG_CAM0_TRIGGER_FREQUENCY = reg;
	update_cam0_timer_pre_values();
	
	return true;
}


/************************************************************************/
/* REG_CAM0_TRIGGER_DURATION_US                                         */
/************************************************************************/
void app_read_REG_CAM0_TRIGGER_DURATION_US(void) {}
bool app_write_REG_CAM0_TRIGGER_DURATION_US(void *a)
{
	uint16_t reg = *((uint16_t*)a);
	
	if (reg < 100 || reg > 5000)
		return false;
	
	if (cam0_acquiring)
		return false;
	
	app_regs.REG_CAM0_TRIGGER_DURATION_US = reg;
	update_cam0_timer_pre_values();
	
	return true;
}


/************************************************************************/
/* REG_RESERVED2                                                        */
/************************************************************************/
void app_read_REG_RESERVED2(void) {}
bool app_write_REG_RESERVED2(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_RESERVED2 = reg;
	return true;
}


/************************************************************************/
/* REG_RESERVED3                                                        */
/************************************************************************/
void app_read_REG_RESERVED3(void) {}
bool app_write_REG_RESERVED3(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_RESERVED3 = reg;
	return true;
}


/************************************************************************/
/* REG_CAM1_TRIGGER_CONFIG                                              */
/************************************************************************/
void app_read_REG_CAM1_TRIGGER_CONFIG(void) {}
bool app_write_REG_CAM1_TRIGGER_CONFIG(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (cam1_acquiring)     return false;
	if (cam1_start_request)	return false;
	
	if (reg & ~GM_TRG_SRC)
		return false;
	else
	{
		switch (reg)
		{
			case MSK_TRG_SRC_INPUT0:
						
				io_pin2in(&PORTC, 0, PULL_IO_TRISTATE, SENSE_IO_EDGE_RISING);	// CAM1 to input
				_delay_us(10);
				set_EN_IN0_TO_CAM1;
				break;
			
			default:
			
				clr_EN_IN0_TO_CAM1;
				_delay_us(10);
				io_pin2out(&PORTC, 0, OUT_IO_DIGITAL, IN_EN_IO_DIS);			// CAM1
		}
	}

	app_regs.REG_CAM1_TRIGGER_CONFIG = reg;
	return true;
}


/************************************************************************/
/* REG_CAM1_TRIGGER_INVERTED                                            */
/************************************************************************/
void app_read_REG_CAM1_TRIGGER_INVERTED(void) {}
bool app_write_REG_CAM1_TRIGGER_INVERTED(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (reg & ~GM_TRIGGER_INVERTED)
		return false;
	
	switch (reg)
	{
		case MSK_TRIGGER_INVERTED_NO:
		
			clr_EN_CAM1_TRIGGER_INV;
			_delay_us(10);
			set_EN_CAM1_TRIGGER_N_INV;
			break;
			
		case MSK_TRIGGER_INVERTED_YES:
		
			clr_EN_CAM1_TRIGGER_N_INV;
			_delay_us(10);		
			set_EN_CAM1_TRIGGER_INV;
			break;
	}	

	app_regs.REG_CAM1_TRIGGER_INVERTED = reg;
	return true;
}


/************************************************************************/
/* REG_CAM1_STROBE_ORIGIN                                               */
/************************************************************************/
void app_read_REG_CAM1_STROBE_SOURCE(void) {}
bool app_write_REG_CAM1_STROBE_SOURCE(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (reg & ~GM_STROBE_SOURCE)
	return false;
	
	switch (reg)
	{
		case MSK_STROBE_DIRECT:
			io_set_int(&PORTD, INT_LEVEL_LOW, 0, (1<<7), true);	// Sets CAM1_STROBE as the interrupt source
			break;
		
		case MSK_STROBE_PULL_UP:
			io_set_int(&PORTD, INT_LEVEL_LOW, 0, (1<<6), true);	// Sets CAM1_STROBE_PU as the interrupt source
			break;
	}
	
	app_regs.REG_CAM1_STROBE_SOURCE = reg;
	return true;
}


/************************************************************************/
/* REG_CAM1_TRIGGER_FREQUENCY                                           */
/************************************************************************/
void app_read_REG_CAM1_TRIGGER_FREQUENCY(void) {}
bool app_write_REG_CAM1_TRIGGER_FREQUENCY(void *a)
{
	uint16_t reg = *((uint16_t*)a);
		
	if (reg < 1 || reg > 1000)
		return false;
	
	if (cam1_acquiring)
		return false;

	app_regs.REG_CAM1_TRIGGER_FREQUENCY = reg;
	update_cam1_timer_pre_values();
	
	return true;
}


/************************************************************************/
/* REG_CAM1_TRIGGER_DURATION_US                                         */
/************************************************************************/
void app_read_REG_CAM1_TRIGGER_DURATION_US(void) {}
bool app_write_REG_CAM1_TRIGGER_DURATION_US(void *a)
{
	uint16_t reg = *((uint16_t*)a);
	
	if (reg < 100 || reg > 5000)
		return false;
	
	if (cam1_acquiring)
		return false;
	
	app_regs.REG_CAM1_TRIGGER_DURATION_US = reg;
	update_cam1_timer_pre_values();
	
	return true;
}


/************************************************************************/
/* REG_RESERVED4                                                        */
/************************************************************************/
void app_read_REG_RESERVED4(void) {}
bool app_write_REG_RESERVED4(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_RESERVED4 = reg;
	return true;
}


/************************************************************************/
/* REG_RESERVED5                                                        */
/************************************************************************/
void app_read_REG_RESERVED5(void) {}
bool app_write_REG_RESERVED5(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_RESERVED5 = reg;
	return true;
}


/************************************************************************/
/* REG_OUT0_CONFIG                                                      */
/************************************************************************/
void app_read_REG_OUT0_CONFIG(void) {}
bool app_write_REG_OUT0_CONFIG(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (reg & ~GM_OUT0_CONFIG)
		return false;
	else
	{
		switch (reg)
		{
			case MSK_OUT0_SOFTWARE:
			case MSK_OUT0_STROBE_CAM0:
			
				clr_EN_CAM0_TO_OUT0;
				_delay_us(10);
				io_pin2out(&PORTD, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);				// OUT0 to output
				break;
			
			case MSK_OUT0_TRIGGER_CAM0:
			
				io_pin2in(&PORTD, 1, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);	// OUT0 to input
				_delay_us(10);				
				set_EN_CAM0_TO_OUT0;
				break;
		}
	}
	
	app_regs.REG_OUT0_CONFIG = reg;
	return true;
}


/************************************************************************/
/* REG_OUT1_CONFIG                                                      */
/************************************************************************/
void app_read_REG_OUT1_CONFIG(void) {}
bool app_write_REG_OUT1_CONFIG(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (reg & ~GM_OUT1_CONFIG)
		return false;
	else
	{
		switch (reg)
		{
			case MSK_OUT1_SOFTWARE:
			case MSK_OUT1_STROBE_CAM1:
			
				clr_EN_CAM1_TO_OUT1;
				_delay_us(10);
				io_pin2out(&PORTC, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);				// OUT1 to output
				break;
			
			case MSK_OUT1_TRIGGER_CAM1:
			
				io_pin2in(&PORTC, 1, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);	// OUT1 to input
				_delay_us(10);
				set_EN_CAM1_TO_OUT1;
				break;
		}
	}

	app_regs.REG_OUT1_CONFIG = reg;
	return true;
}


/************************************************************************/
/* REG_RESERVED6                                                        */
/************************************************************************/
void app_read_REG_RESERVED6(void) {}
bool app_write_REG_RESERVED6(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	app_regs.REG_RESERVED6 = reg;
	return true;
}


/************************************************************************/
/* REG_RESERVED7                                                        */
/************************************************************************/
void app_read_REG_RESERVED7(void) {}
bool app_write_REG_RESERVED7(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_RESERVED7 = reg;
	return true;
}


/************************************************************************/
/* REG_OUT_SET                                                          */
/************************************************************************/
void app_read_REG_OUT_SET(void) {}
bool app_write_REG_OUT_SET(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (app_regs.REG_OUT0_CONFIG == MSK_OUT0_SOFTWARE)
		if (reg & B_OUT0)
			set_io(PORTD, 1);
	
	if (app_regs.REG_OUT1_CONFIG == MSK_OUT1_SOFTWARE)
		if (reg & B_OUT1)
			set_io(PORTC, 1);

	app_regs.REG_OUT_SET = reg;
	return true;
}


/************************************************************************/
/* REG_OUT_CLEAR                                                        */
/************************************************************************/
void app_read_REG_OUT_CLEAR(void) {}
bool app_write_REG_OUT_CLEAR(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (app_regs.REG_OUT0_CONFIG == MSK_OUT0_SOFTWARE)
		if (reg & B_OUT0)
			clear_io(PORTD, 1);
	
	if (app_regs.REG_OUT1_CONFIG == MSK_OUT1_SOFTWARE)
		if (reg & B_OUT1)
			clear_io(PORTC, 1);

	app_regs.REG_OUT_CLEAR = reg;
	return true;
}


/************************************************************************/
/* REG_OUT_TOGGLE                                                       */
/************************************************************************/
void app_read_REG_OUT_TOGGLE(void) {}
bool app_write_REG_OUT_TOGGLE(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (app_regs.REG_OUT0_CONFIG == MSK_OUT0_SOFTWARE)
		if (reg & B_OUT0)
			toggle_io(PORTD, 1);
	
	if (app_regs.REG_OUT1_CONFIG == MSK_OUT1_SOFTWARE)
		if (reg & B_OUT1)
			toggle_io(PORTC, 1);

	app_regs.REG_OUT_TOGGLE = reg;
	return true;
}


/************************************************************************/
/* REG_OUT_WRITE                                                        */
/************************************************************************/
void app_read_REG_OUT_WRITE(void)
{
	app_regs.REG_OUT_WRITE  = (read_OUT0) ? B_OUT0 : 0;
	app_regs.REG_OUT_WRITE |= (read_OUT1) ? B_OUT1 : 0;
}

bool app_write_REG_OUT_WRITE(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	
	if (app_regs.REG_OUT0_CONFIG == MSK_OUT0_SOFTWARE)
	{
		if (reg & B_OUT0)
			set_io(PORTD, 1);
		else
			clear_io(PORTD, 1);
	}
	
	if (app_regs.REG_OUT1_CONFIG == MSK_OUT1_SOFTWARE)
	{
		if (reg & B_OUT1)
			set_io(PORTC, 1);
		else
			clear_io(PORTC, 1);
	}

	app_regs.REG_OUT_WRITE = reg;
	return true;
}


/************************************************************************/
/* REG_IN_STATE                                                         */
/************************************************************************/
void app_read_REG_IN_STATE(void)
{
	app_regs.REG_IN_STATE = (read_INPUT0) ? B_IN0 : 0;
}

bool app_write_REG_IN_STATE(void *a) { return false; }