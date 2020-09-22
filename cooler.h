#ifndef __COOLER_H__
#define __COOLER_H__

typedef enum
{
    COOLER_OFF = 0,
    COOLER_ON
} cooler_state;

void cooler_init(void);
void cooler_on(void);
void cooler_off (void);
cooler_state cooler_getState (void);


#endif // __COOLER_H__
