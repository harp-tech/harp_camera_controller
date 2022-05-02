#include "cpu.h"
#include "hwbp_core_types.h"
#include "app_ios_and_regs.h"
#include "app_funcs.h"
#include "hwbp_core.h"

/************************************************************************/
/* Declare application registers                                        */
/************************************************************************/
extern AppRegs app_regs;

/************************************************************************/
/* Interrupts from Timers                                               */
/************************************************************************/
// ISR(TCC0_OVF_vect, ISR_NAKED)
// ISR(TCD0_OVF_vect, ISR_NAKED)
// ISR(TCE0_OVF_vect, ISR_NAKED)
// ISR(TCF0_OVF_vect, ISR_NAKED)
// 
// ISR(TCC0_CCA_vect, ISR_NAKED)
// ISR(TCD0_CCA_vect, ISR_NAKED)
// ISR(TCE0_CCA_vect, ISR_NAKED)
// ISR(TCF0_CCA_vect, ISR_NAKED)
// 
// ISR(TCD1_OVF_vect, ISR_NAKED)
// 
// ISR(TCD1_CCA_vect, ISR_NAKED)



/************************************************************************/
/* CAMERA 0                                                             */
/************************************************************************/
extern bool cam0_acquiring;
extern bool cam0_is_using_fixed_frequency;
extern bool stop_cam0_when_possible;

uint32_t cam0_int_s;
uint16_t cam0_int_us;

ISR(TCD0_OVF_vect, ISR_NAKED)
{
	if (cam0_is_using_fixed_frequency)
	{
		clear_io(PORTD, 0);
		TCD0_CTRLA = 0;
		
		if (stop_cam0_when_possible)
		{		
			stop_cam0_when_possible = false;
			cam0_acquiring = false;
			
			cam0_is_using_fixed_frequency = false;
			clr_LED_CAM0;	
		}
	}
	else
	{
		core_func_mark_user_timestamp();
		core_func_read_user_timestamp(&cam0_int_s, &cam0_int_us);
	}
	
	reti();
}

ISR(TCD0_CCA_vect, ISR_NAKED)
{
	if (stop_cam0_when_possible)
	{
		stop_cam0_when_possible = false;
		cam0_acquiring = false;
		
		timer_type0_stop(&TCD0);
		clr_LED_CAM0;
	}	
	
	if (app_regs.REG_CAM0_EVENT_CONFIG == MSK_EVENT_ON_TRIGGER)
	{
		app_regs.REG_CAM0_EVENT = B_TRIGGER;
		core_func_update_user_timestamp(cam0_int_s, cam0_int_us);
		core_func_send_event(ADD_REG_CAM0_EVENT, false);
	}
	
	reti();
}


/************************************************************************/
/* CAMERA 1                                                             */
/************************************************************************/
extern bool cam1_acquiring;
extern bool cam1_is_using_fixed_frequency;
extern bool stop_cam1_when_possible;

uint32_t cam1_int_s;
uint16_t cam1_int_us;

ISR(TCC0_OVF_vect, ISR_NAKED)
{
	if (cam1_is_using_fixed_frequency)
	{
		clear_io(PORTC, 0);
		TCC0_CTRLA = 0;
		
		if (stop_cam1_when_possible)
		{		
			stop_cam1_when_possible = false;
			cam1_acquiring = false;
			
			cam1_is_using_fixed_frequency = false;
			clr_LED_CAM1;	
		}
	}
	else
	{
		core_func_mark_user_timestamp();
		core_func_read_user_timestamp(&cam1_int_s, &cam1_int_us);
	}
	
	reti();
}

ISR(TCC0_CCA_vect, ISR_NAKED)
{
	if (stop_cam1_when_possible)
	{
		stop_cam1_when_possible = false;
		cam1_acquiring = false;
		
		timer_type0_stop(&TCC0);
		clr_LED_CAM1;
	}
	
	if (app_regs.REG_CAM1_EVENT_CONFIG == MSK_EVENT_ON_TRIGGER)
	{
		app_regs.REG_CAM1_EVENT = B_TRIGGER;
		core_func_update_user_timestamp(cam1_int_s, cam1_int_us);
		core_func_send_event(ADD_REG_CAM1_EVENT, false);
	}
	
	reti();
}

/************************************************************************/ 
/* CAM0_STROBE and CAM0_STROBE_PU                                       */
/************************************************************************/
ISR(PORTA_INT0_vect, ISR_NAKED)
{	
	bool strobe_up;
	
	if (app_regs.REG_CAM0_STROBE_SOURCE == MSK_STROBE_DIRECT)
		strobe_up = read_CAM0_STROBE ? true : false;
	else
		strobe_up = read_CAM0_STROBE_PU ? true : false;
	
	if (strobe_up)
	{
		if (app_regs.REG_CAM0_EVENT_CONFIG == MSK_EVENT_ON_STROBE)
		{
			app_regs.REG_CAM0_EVENT = B_STROBE;
			core_func_send_event(ADD_REG_CAM0_EVENT, true);
		}
			
		if (app_regs.REG_OUT0_CONFIG == MSK_OUT0_STROBE_CAM0)
		{
			set_io(PORTD, 1);
		}
	}
	else
	{
		if (app_regs.REG_OUT0_CONFIG == MSK_OUT0_STROBE_CAM0)
		{
			clear_io(PORTD, 1);
		}
	}
	
	reti();
}

/************************************************************************/ 
/* CAM1_STROBE and CAM1_STROBE_PU                                       */
/************************************************************************/
ISR(PORTD_INT0_vect, ISR_NAKED)
{
	bool strobe_up;
	
	if (app_regs.REG_CAM1_STROBE_SOURCE == MSK_STROBE_DIRECT)
		strobe_up = read_CAM1_STROBE ? true : false;
	else
		strobe_up = read_CAM1_STROBE_PU ? true : false;
	
	if (strobe_up)
	{
		if (app_regs.REG_CAM1_EVENT_CONFIG == MSK_EVENT_ON_STROBE)
		{
			app_regs.REG_CAM1_EVENT = B_STROBE;
			core_func_send_event(ADD_REG_CAM1_EVENT, true);
		}
		
		if (app_regs.REG_OUT1_CONFIG == MSK_OUT1_STROBE_CAM1)
		{
			set_io(PORTC, 1);
		}
	}
	else
	{
		if (app_regs.REG_OUT1_CONFIG == MSK_OUT1_STROBE_CAM1)
		{
			clear_io(PORTC, 1);
		}
	}
	
	reti();
}

/************************************************************************/ 
/* INPUT0                                                               */
/************************************************************************/
bool input0_previous_state = false;

ISR(PORTB_INT1_vect, ISR_NAKED)
{
	if (read_INPUT0)
	{
		if (!input0_previous_state)
		{
			input0_previous_state = true;
		
			if ((app_regs.REG_CAM0_TRIGGER_CONFIG != MSK_TRG_SRC_INPUT0) && (app_regs.REG_CAM1_TRIGGER_CONFIG != MSK_TRG_SRC_INPUT0))
			{
				app_regs.REG_IN_STATE = B_IN0;
				core_func_send_event(ADD_REG_IN_STATE, true);
			}
		}
	}
	else
	{
		if (input0_previous_state)
		{
			input0_previous_state = false;
			
			if ((app_regs.REG_CAM0_TRIGGER_CONFIG != MSK_TRG_SRC_INPUT0) && (app_regs.REG_CAM1_TRIGGER_CONFIG != MSK_TRG_SRC_INPUT0))
			{
				app_regs.REG_IN_STATE = 0;
				core_func_send_event(ADD_REG_IN_STATE, true);
			}
		}
	}	
	
	reti();
}

/************************************************************************/ 
/* CAM0                                                                 */
/************************************************************************/
ISR(PORTD_INT1_vect, ISR_NAKED)
{
	if (read_CAM0)
		if (app_regs.REG_CAM0_EVENT_CONFIG == MSK_EVENT_ON_TRIGGER)
			if (app_regs.REG_CAM0_TRIGGER_CONFIG == MSK_TRG_SRC_INPUT0)
			{
				app_regs.REG_CAM0_EVENT = B_TRIGGER;
				core_func_send_event(ADD_REG_CAM0_EVENT, true);
				
				if (core_bool_is_visual_enabled())
					set_LED_CAM0;
			}
	
	reti();
}

/************************************************************************/ 
/* CAM1                                                                 */
/************************************************************************/
ISR(PORTC_INT1_vect, ISR_NAKED)
{
	if (read_CAM1)
		if (app_regs.REG_CAM1_EVENT_CONFIG == MSK_EVENT_ON_TRIGGER)
			if (app_regs.REG_CAM1_TRIGGER_CONFIG == MSK_TRG_SRC_INPUT0)
			{
				app_regs.REG_CAM0_EVENT = B_TRIGGER;
				core_func_send_event(ADD_REG_CAM0_EVENT, true);
				
				if (core_bool_is_visual_enabled())
					set_LED_CAM1;
			}
	
	reti();
}

