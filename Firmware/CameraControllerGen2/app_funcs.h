#ifndef _APP_FUNCTIONS_H_
#define _APP_FUNCTIONS_H_
#include <avr/io.h>


/************************************************************************/
/* Define if not defined                                                */
/************************************************************************/
#ifndef bool
	#define bool uint8_t
#endif
#ifndef true
	#define true 1
#endif
#ifndef false
	#define false 0
#endif


/************************************************************************/
/* Prototypes                                                           */
/************************************************************************/
void app_read_REG_CAM0_EVENT(void);
void app_read_REG_CAM1_EVENT(void);
void app_read_REG_CAM0_EVENT_CONFIG(void);
void app_read_REG_CAM1_EVENT_CONFIG(void);
void app_read_REG_START_AND_STOP(void);
void app_read_REG_START_AND_STOP_TIMESTAMPED(void);
void app_read_REG_START_TIMESTAMP(void);
void app_read_REG_STOP_TIMESTAMP(void);
void app_read_REG_RESERVED0(void);
void app_read_REG_RESERVED1(void);
void app_read_REG_CAM0_TRIGGER_CONFIG(void);
void app_read_REG_CAM0_TRIGGER_INVERTED(void);
void app_read_REG_CAM0_STROBE_SOURCE(void);
void app_read_REG_CAM0_TRIGGER_FREQUENCY(void);
void app_read_REG_CAM0_TRIGGER_DURATION_US(void);
void app_read_REG_RESERVED2(void);
void app_read_REG_RESERVED3(void);
void app_read_REG_CAM1_TRIGGER_CONFIG(void);
void app_read_REG_CAM1_TRIGGER_INVERTED(void);
void app_read_REG_CAM1_STROBE_SOURCE(void);
void app_read_REG_CAM1_TRIGGER_FREQUENCY(void);
void app_read_REG_CAM1_TRIGGER_DURATION_US(void);
void app_read_REG_RESERVED4(void);
void app_read_REG_RESERVED5(void);
void app_read_REG_OUT0_CONFIG(void);
void app_read_REG_OUT1_CONFIG(void);
void app_read_REG_RESERVED6(void);
void app_read_REG_RESERVED7(void);
void app_read_REG_OUT_SET(void);
void app_read_REG_OUT_CLEAR(void);
void app_read_REG_OUT_TOGGLE(void);
void app_read_REG_OUT_WRITE(void);
void app_read_REG_IN_STATE(void);

bool app_write_REG_CAM0_EVENT(void *a);
bool app_write_REG_CAM1_EVENT(void *a);
bool app_write_REG_CAM0_EVENT_CONFIG(void *a);
bool app_write_REG_CAM1_EVENT_CONFIG(void *a);
bool app_write_REG_START_AND_STOP(void *a);
bool app_write_REG_START_AND_STOP_TIMESTAMPED(void *a);
bool app_write_REG_START_TIMESTAMP(void *a);
bool app_write_REG_STOP_TIMESTAMP(void *a);
bool app_write_REG_RESERVED0(void *a);
bool app_write_REG_RESERVED1(void *a);
bool app_write_REG_CAM0_TRIGGER_CONFIG(void *a);
bool app_write_REG_CAM0_TRIGGER_INVERTED(void *a);
bool app_write_REG_CAM0_STROBE_SOURCE(void *a);
bool app_write_REG_CAM0_TRIGGER_FREQUENCY(void *a);
bool app_write_REG_CAM0_TRIGGER_DURATION_US(void *a);
bool app_write_REG_RESERVED2(void *a);
bool app_write_REG_RESERVED3(void *a);
bool app_write_REG_CAM1_TRIGGER_CONFIG(void *a);
bool app_write_REG_CAM1_TRIGGER_INVERTED(void *a);
bool app_write_REG_CAM1_STROBE_SOURCE(void *a);
bool app_write_REG_CAM1_TRIGGER_FREQUENCY(void *a);
bool app_write_REG_CAM1_TRIGGER_DURATION_US(void *a);
bool app_write_REG_RESERVED4(void *a);
bool app_write_REG_RESERVED5(void *a);
bool app_write_REG_OUT0_CONFIG(void *a);
bool app_write_REG_OUT1_CONFIG(void *a);
bool app_write_REG_RESERVED6(void *a);
bool app_write_REG_RESERVED7(void *a);
bool app_write_REG_OUT_SET(void *a);
bool app_write_REG_OUT_CLEAR(void *a);
bool app_write_REG_OUT_TOGGLE(void *a);
bool app_write_REG_OUT_WRITE(void *a);
bool app_write_REG_IN_STATE(void *a);


#endif /* _APP_FUNCTIONS_H_ */