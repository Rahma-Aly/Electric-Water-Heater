#ifndef __SSD_H__
#define __SSD_H__

typedef enum
{
    SSD_UNITS,
    SSD_TENS
} SSD;

typedef enum
{
    SSD_OFF = 0,
    SSD_ON
} ssd_state;

typedef enum
{
    SSD_0 = 0,
    SSD_1,
    SSD_2,
    SSD_3,
    SSD_4,
    SSD_5,
    SSD_6,
    SSD_7,
    SSD_8,
    SSD_9,
    SSD_NULL
} ssd_symbol;

void ssd_init(void);
void ssd_update (void);
void ssd_setSymbol (SSD ssd, ssd_symbol symbol);
ssd_symbol ssd_getSymbol (SSD ssd);
void ssd_setState(SSD ssd, ssd_state state);
ssd_state ssd_getState (SSD ssd);

#endif // __SSD_H__
