#ifndef __PB_H__
#define __PB_H__

typedef enum
{
   PB_UP = 0,
   PB_DOWN,
   PB_ON_OFF
} PB;

typedef enum
{
    PB_R,
    PB_PP,
    PB_P,
    PB_PR
} pb_state;

void pb_init(void);
void pb_update(void);
pb_state pb_getState (PB pb);

#endif // __PB_H__
