#include "display.h"
#include "ssd.h"
#include "sensor.h"
#include "timer.h"
#include "tempControl.h"



#define DIS_BLINK_MS (1000) //1 sec
#define DIS_PERIOD_MS (100)


static void display_off (void);
static void display_on (void);
static void display_blink(void);

void display_init(void)
{
    ssd_init();

    display_off ();
}


void display_update(void)
{
    static unsigned int display_counter = 0;

    display_counter += TMR_TICK_MS;

    if (display_counter != DIS_PERIOD_MS)
    {
        return;
    }

    display_counter = 0;

    switch (get_state())
    {
       case OFF_STATE:
           display_off();
           break;
       case NORMAL_STATE:
           display_on();
           break;
       case SET_TEMP_STATE:
           display_blink();
           break;
    }
}

static void display_on (void)
{
    unsigned int temp;

    temp = sensor_getTemp();

    ssd_setSymbol(SSD_TENS, temp/10);
    ssd_setSymbol(SSD_UNITS, temp%10);

}

static void display_off (void)
{
    ssd_setSymbol(SSD_TENS, SSD_NULL);
    ssd_setSymbol(SSD_UNITS, SSD_NULL);
}

static void display_blink(void)
{
    static unsigned int blink_counter = 0;

     blink_counter += DIS_PERIOD_MS;

     if (blink_counter == DIS_BLINK_MS)
     {
         blink_counter = 0;

        if ((ssd_getSymbol(SSD_UNITS) == SSD_NULL) && (ssd_getSymbol(SSD_TENS) == SSD_NULL))
         {
            ssd_setSymbol(SSD_UNITS, get_reqTemp()%10);
            ssd_setSymbol(SSD_TENS, get_reqTemp()/10);
         }
          else
         {
            ssd_setSymbol(SSD_UNITS, SSD_NULL);
            ssd_setSymbol(SSD_TENS, SSD_NULL);
         }
     }
}

