#include "cooler.h"
#include "main.h"
#include "port.h"

static cooler_state state;

void cooler_init(void)
{
    GPIO_InitPortPin(COOLER_PORT_CR, COOLER_PIN, GPIO_OUT);
    cooler_off();
}

void cooler_on(void)
{
      GPIO_WritePortPin(COOLER_PORT_DR, COOLER_PIN, COOLER_ON);
      state = COOLER_ON;
}
void cooler_off (void)
{
      GPIO_WritePortPin(COOLER_PORT_DR, COOLER_PIN, COOLER_OFF);
      state = COOLER_OFF;
}


cooler_state cooler_getState (void)
{
    return state;
}
