#include "sensor.h"
#include "timer.h"
#include "adc.h"



#define SENSOR_PERIOD_MS (100)

static unsigned int readings[10] = {0};
static unsigned int sensed_temp;
static unsigned int avg_temp;

unsigned int sensor_getTemp(void)
{
    return sensed_temp;
}

void sensor_update(void)
{
    static unsigned int temp_counter = 0;

    temp_counter += TMR_TICK_MS;

    if (temp_counter != SENSOR_PERIOD_MS)
    {
        return;
    }
      temp_counter = 0;

    sensed_temp = (adc_getResult(2) * 100/204);

}

unsigned int sensor_getavgTemp (void)
{
    unsigned char i;
    unsigned int sum = 0;

    for (i = 0 ; i < 10 ; i++)
    {
        if (i == 9)
        {
            readings[i] = sensed_temp;
        }
        else
        {
            readings[i] = readings[i+1];
        }
        sum += readings [i];
    }

       avg_temp = sum / 10;

    return avg_temp;
}




