#include "timer.h"
#include "main.h"
#include "port.h"
#include "ssd.h"
#include "led.h"
#include "pb.h"
#include "tempControl.h"
#include "display.h"
#include "sensor.h"

void TMR_Init(void)
{
    TMR_SET_PRESCALER_256;
	TMR_DISABLE_CLOCK;
}
void TMR_Start(void)
{
   	TMR_CLEAR_FLAG;
	TMR_UPDATE_REGISTER(TMR_TICK_MS);
	TMR_ENABLE_INTERRUPT;
	GLOBAL_INTERRUPT_ENABLE;
	TMR_ENABLE_CLOCK;

}

unsigned char TMR_CheckOverFlow(void)
{
   return TMR_GET_FLAG;
}
void TMR_Stop(void)
{
    TMR_DISABLE_CLOCK;
}
void TMR_Update(void) __interrupt 0
{
    TMR_CLEAR_FLAG;
    TMR_UPDATE_REGISTER(TMR_TICK_MS);

    pb_update();
    ssd_update();
    display_update();
    sensor_update();
    tempControl_update();
    led_update();


}
