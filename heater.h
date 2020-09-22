#ifndef __HEATER_H__
#define __HEATER_H__

typedef enum
{
    HEATER_OFF = 0,
    HEATER_ON
} heater_state;

void heater_init(void);
void heater_on(void);
void heater_off(void);
heater_state heater_getState (void);


#endif // __HEATER_H__
