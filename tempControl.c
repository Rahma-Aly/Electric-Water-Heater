#include "tempControl.h"
#include "sensor.h"
#include "cooler.h"
#include "heater.h"
#include "timer.h"
#include "ext_e2prom.h"
#include "pb.h"


#define PRE_SET_TEMP (60)
#define MIN_TEMP     (35)
#define MAX_TEMP     (75)

#define TEMP_STEP    (5)

#define CONTROL_PERIOD_MS (20)
#define LEAVE_SET_TEMP_MODE (5000)


static void temp_actions (void);
static void setting_actions(void);

static unsigned int req_temp;
static control_state Cstate = OFF_STATE;

void tempControl_init()
{
    cooler_init();
    heater_init();

    req_temp = PRE_SET_TEMP;
    write_ext_e2prom(0x0020, req_temp);

}

void tempControl_update (void)
{
    static unsigned int control_counter = 0;

    control_counter += TMR_TICK_MS;

    if (control_counter != CONTROL_PERIOD_MS)
    {
        return;
    }

    control_counter = 0;

    switch (Cstate)
    {
       case OFF_STATE:
           heater_off();
           cooler_off();
           if (pb_getState(PB_ON_OFF) == PB_PP)
           {
               Cstate = NORMAL_STATE;
           }
           break;

       case NORMAL_STATE:
           temp_actions();
        if (pb_getState(PB_ON_OFF) == PB_PP)
        {
            Cstate = OFF_STATE;
        }
        else if((pb_getState(PB_DOWN) == PB_PR) || (pb_getState(PB_UP) == PB_PR))
        {
            Cstate = SET_TEMP_STATE;
        }
        break;

       case SET_TEMP_STATE:
        setting_actions();
        if (pb_getState(PB_ON_OFF) == PB_PP)
        {
            Cstate = OFF_STATE;
        }
        break;
    }

}

unsigned int get_reqTemp(void)
{
    return req_temp;
}

static void temp_actions (void)
{
    heater_state hstate;
    cooler_state cstate;
    unsigned int avg_sensed_temp;

    avg_sensed_temp = sensor_getavgTemp();

    hstate = heater_getState();
    cstate = cooler_getState();

    if( (hstate == HEATER_OFF) &&(cstate == COOLER_OFF))
    {
        if(avg_sensed_temp <= (req_temp - 5))
        {
            heater_on();
        }
        else if (avg_sensed_temp >= (req_temp + 5))
        {
            cooler_on();
        }
    }
    else if ((hstate == HEATER_ON) && (avg_sensed_temp == req_temp ))
    {
        heater_off();
    }
    else if ((cstate == COOLER_ON) && (avg_sensed_temp == req_temp))
    {
        cooler_off();
    }

}

static void setting_actions(void)
{
   static unsigned int leave_counter = 0;

   req_temp = read_ext_e2prom(0x0020);
    if (req_temp == 0x00FF)
    {
        req_temp = PRE_SET_TEMP;
        write_ext_e2prom(0x0020, req_temp);
    }

   if (pb_getState(PB_UP)== PB_PP)
   {
        leave_counter = 0;
        req_temp += TEMP_STEP;
        if (req_temp > MAX_TEMP)
        {
            req_temp = MAX_TEMP;
        }
   }
   else if (pb_getState(PB_DOWN)== PB_PP)
    {
        leave_counter = 0;
        req_temp -= TEMP_STEP;
        if (req_temp < MIN_TEMP)
        {
            req_temp = MIN_TEMP;
        }
    }
    else
    {
        leave_counter += CONTROL_PERIOD_MS;

        if (leave_counter == LEAVE_SET_TEMP_MODE)
        {
            Cstate = NORMAL_STATE;
            leave_counter = 0;
            return;
        }
    }
    write_ext_e2prom(0x0020, req_temp);

}

control_state get_state(void)
{
    return Cstate;
}
