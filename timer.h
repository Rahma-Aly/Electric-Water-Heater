#ifndef __TIMER_H__
#define __TIMER_H__

#define TMR_INTERRUPT_ENABLE

#define TMR_TICK_MS	(5)


void TMR_Init(void);
void TMR_Start(void);
unsigned char TMR_CheckOverFlow(void);
void TMR_Stop(void);
void TMR_Update(void) __interrupt 0;

#endif // __TIMER_H__
