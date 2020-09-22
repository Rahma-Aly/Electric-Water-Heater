#include "led.h"
#include "main.h"
#include "port.h"
#include "cooler.h"
#include "heater.h"
#include "timer.h"


#define LED_BLINK_PERIOD_MS (1000) //1SEC
#define LED_PERIOD_MS (20)

static void led_on (void);
static void led_off (void);
static void led_toggle(void);

void led_init(void)
{
    GPIO_InitPortPin(LED_HEATING_CR, LED_HEATING_PIN, GPIO_OUT);
    led_off();
}

void led_update(void)
{
    static unsigned int led_counter = 0;
   cooler_state Cstate = cooler_getState();
   heater_state Hstate = heater_getState();

   led_counter += TMR_TICK_MS;

   if(led_counter != LED_PERIOD_MS)
   {
       return;
   }

   led_counter = 0;

    if ((Cstate == COOLER_OFF) &&(Hstate == HEATER_OFF))
    {
        led_off();
    }
    else if (Cstate == COOLER_ON)
    {
        led_on();
    }
    else if (Hstate == HEATER_ON)
    {
        led_toggle();
    }

}

static void led_toggle(void)
{
    static unsigned int LED_counter = 0 ;

    LED_counter += LED_PERIOD_MS;

    if (LED_counter != LED_BLINK_PERIOD_MS)
    {
        return;
    }
    LED_counter = 0;

    if (GPIO_ReadPortPin(LED_HEATING_DR, LED_HEATING_PIN)== LED_OFF)
    {
          led_on();
    }
    else
    {
        led_off();
    }



}

static void led_on (void)
{
    GPIO_WritePortPin(LED_HEATING_DR, LED_HEATING_PIN, LED_ON);
}
static void led_off (void)
{
    GPIO_WritePortPin(LED_HEATING_DR, LED_HEATING_PIN, LED_OFF);
}
