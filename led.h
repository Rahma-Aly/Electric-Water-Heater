#ifndef __LED_H__
#define __LED_H__

typedef enum
{
    LED_OFF = 0,
    LED_ON = 1
} led_state;

void led_init(void);
void led_update(void);

#endif // __LED_H__
