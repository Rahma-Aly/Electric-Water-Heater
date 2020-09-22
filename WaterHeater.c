#include "main.h"
#include "display.h"
#include "tempControl.h"
#include "led.h"
#include "timer.h"
#include "pb.h"
#include "adc.h"
#include "ext_e2prom.h"

unsigned int  __at(0x2007) CONFIG = _HS_OSC & _WDT_OFF & _PWRTE_ON & _BODEN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _DEBUG_OFF & _CP_OFF;

void main (void)
{
    ext_e2prom_init();

    led_init();

    pb_init();

    adc_init(1);

    tempControl_init();

    display_init();

    TMR_Init();

    TMR_Start();

    while(1)
    {

    }
}
