#include "pb.h"
#include "main.h"
#include "port.h"
#include "timer.h"


#define PB_PERIOD_MS (20)

#define NUMBER_OF_SAMPLE (2)
#define NUMBER_OF_PB     (3)

#define PB_P_VOLTAGE  (0)
#define PB_R_VOLTAGE  (1)

typedef struct
{
    unsigned char samples[NUMBER_OF_SAMPLE];
    pb_state PB_state;
} PB_info;

static PB_info pb_info [NUMBER_OF_PB];

void pb_init(void)
{
    unsigned char button =  0;

    //HW INITIALIZATION
    GPIO_InitPortPin (PB_UP_PORT_CR, PB_UP_PIN, GPIO_IN);
    GPIO_InitPortPin (PB_DOWN_PORT_CR, PB_DOWN_PIN, GPIO_IN);
    GPIO_InitPortPin (PB_ON_OFF_PORT_CR, PB_ON_OFF_PIN, GPIO_IN);

     //STATE AND SAMPLE INITIALIZATION
    for ( button = PB_UP; button < NUMBER_OF_PB; button++)
    {
        pb_info[button].PB_state = PB_R;

        pb_info[button].samples[0] = PB_R_VOLTAGE;
        pb_info[button].samples[1] = PB_R_VOLTAGE;

    }

}

void pb_update(void)
{
    static unsigned int pb_counter = 0;
    unsigned char button = 0;

    pb_counter += TMR_TICK_MS;

    if (pb_counter != PB_PERIOD_MS)
    {
        return;
    }

    pb_counter = 0;

    for (button = PB_UP; button <= PB_ON_OFF; button ++)
    {
        //SAMPLE UPDATE
        pb_info[button].samples[0] = pb_info[button].samples[1];
        switch (button)
        {
         case PB_UP:
             pb_info[button].samples[1] = GPIO_ReadPortPin(PB_UP_PORT_DR , PB_UP_PIN); break;
         case PB_DOWN:
             pb_info[button].samples[1] = GPIO_ReadPortPin(PB_DOWN_PORT_DR , PB_DOWN_PIN); break;
         case PB_ON_OFF:
             pb_info[button].samples[1] = GPIO_ReadPortPin(PB_ON_OFF_PORT_DR , PB_ON_OFF_PIN); break;
        }
         //STATE UPDATE
        switch (pb_info[button].PB_state)
        {
          case PB_R:
             if((pb_info[button].samples[0] == PB_P_VOLTAGE) &&
               (pb_info[button].samples[1] == PB_P_VOLTAGE))
            {
                pb_info[button].PB_state = PB_PP;
            }
            break;
          case PB_PP:
            if(pb_info[button].samples[1] == PB_P_VOLTAGE)
            {
                pb_info[button].PB_state = PB_P;
            }
            break;
          case PB_P:
              if((pb_info[button].samples[0] == PB_R_VOLTAGE) &&
               (pb_info[button].samples[1] == PB_R_VOLTAGE))
            {
                pb_info[button].PB_state = PB_PR;
            }
            break;
          case PB_PR:
            if(pb_info[button].samples[1] == PB_R_VOLTAGE)
            {
                pb_info[button].PB_state = PB_R;
            }
            break;
        }
    }

}

pb_state pb_getState (PB pb)
{
    return pb_info[pb].PB_state;
}
