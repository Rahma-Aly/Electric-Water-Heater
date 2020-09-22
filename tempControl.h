#ifndef __TEMPCONTROL_H__
#define __TEMPCONTROL_H__

typedef enum
{
    OFF_STATE = 0,
    NORMAL_STATE,
    SET_TEMP_STATE
} control_state;


void tempControl_init (void);
void tempControl_update (void);
control_state get_state(void);
unsigned int get_reqTemp(void);





#endif // __TEMPCONTROL_H__
