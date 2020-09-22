#include "heater.h"
#include "main.h"
#include "port.h"



static heater_state state;

void heater_init(void)
{
    GPIO_InitPortPin(HEATER_PORT_CR, HEATER_PIN, GPIO_OUT);
    heater_off();

}
void heater_on(void)
{
   GPIO_WritePortPin(HEATER_PORT_DR, HEATER_PIN, HEATER_ON);
   state = HEATER_ON;

}
void heater_off(void)
{
    GPIO_WritePortPin(HEATER_PORT_DR, HEATER_PIN, HEATER_OFF);
    state = HEATER_OFF;
}
heater_state heater_getState (void)
{
    return state;
}
