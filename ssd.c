#include "ssd.h"
#include "main.h"
#include "port.h"
#include "timer.h"


#define SSD_NUM (2)
#define SSD_PERIOD_MS (5)

static ssd_symbol ssd_symbols[SSD_NUM] = {SSD_NULL};

static unsigned char ssd_data[] =
{
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
    0b00000000,
};

static void ssd_out(SSD ssd, ssd_symbol symbol);

void ssd_init(void)
{
    //DATA PINS INITIALIZATION
    GPIO_InitPort(SSD_DATA_PORT_CR, GPIO_OUT);
    ssd_out(SSD_TENS, SSD_NULL);
    ssd_out(SSD_UNITS, SSD_NULL);

    // STATE PINS INITIALIZATION
    //each of those pins controls which SSD will function
    GPIO_InitPortPin(SSD_UNITS_CR, SSD_UNITS_PIN, GPIO_OUT);
    GPIO_InitPortPin(SSD_TENS_CR, SSD_TENS_PIN, GPIO_OUT);

    //STATE INITIALIZATION
    ssd_setState(SSD_UNITS, SSD_OFF);
    ssd_setState(SSD_TENS, SSD_OFF);
}

void ssd_update (void)
{
    static unsigned int ssd_counter = 0;
    static SSD current_ssd = SSD_UNITS;

    ssd_counter += TMR_TICK_MS;

    if (ssd_counter != SSD_PERIOD_MS )
    {
        return;
    }
    ssd_counter = 0;

    ssd_out(current_ssd, ssd_symbols[current_ssd]);

    if (current_ssd == SSD_TENS)
      current_ssd = SSD_UNITS;
      else
        current_ssd++;
}

void ssd_setSymbol (SSD ssd, ssd_symbol symbol)
{
    ssd_symbols[ssd] = symbol;
}

ssd_symbol ssd_getSymbol (SSD ssd)
{
    return ssd_symbols[ssd];
}

void ssd_setState(SSD ssd, ssd_state state)
{
    switch (ssd)
    {
      case SSD_UNITS:
        GPIO_WritePortPin (SSD_UNITS_DR , SSD_UNITS_PIN, state); break;
      case SSD_TENS:
        GPIO_WritePortPin(SSD_TENS_DR, SSD_TENS_PIN, state); break;
    }
}

ssd_state ssd_getState (SSD ssd)
{
    ssd_state state = SSD_OFF;
    switch (ssd)
    {
    case SSD_UNITS:
         state = GPIO_ReadPortPin(SSD_UNITS_DR , SSD_UNITS_PIN); break;
    case SSD_TENS:
        state = GPIO_ReadPortPin( SSD_TENS_DR , SSD_TENS_PIN); break;
    }

    return state;
}

static void ssd_out(SSD ssd, ssd_symbol symbol)
{
    ssd_setState(SSD_UNITS, SSD_OFF);
    ssd_setState(SSD_TENS, SSD_OFF);

    GPIO_WritePort(SSD_DATA_PORT_DR, ssd_data[symbol]);

    ssd_setState(ssd, SSD_ON);
}

