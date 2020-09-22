#ifndef __ADC_H__
#define __ADC_H__


void adc_init(unsigned char clk);
unsigned int adc_getResult(unsigned char channel);


#endif // __ADC_H__
