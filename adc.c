#include "adc.h"
#include <pic16f877a.h>


#define ADC_SELECT_CHANNEL(channel)	(CHS2 = ((channel & 0x4) >> 2));\
                                    (CHS1 = ((channel & 0x2) >> 1));\
                                    (CHS0 = (channel & 0x1))


#define ADC_SET_STATE(x)	(ADON = x)

#define ADC_SELECT_VREFP(x)
#define ADC_SELECT_VREFN(x)

#define ADC_SELECT_RESULT_JUSTIFICATION(justification)	(ADFM = justification)

#define ADC_READ_RESULT(justification) (justification)?(((unsigned int)((unsigned int)ADRESH)<<8)|(ADRESL)):((((unsigned int)ADRESH)<<2)|(ADRESL>>6))

#define ADC_START_CONVERSION() (GO = 1)

#define ADC_WAIT_FOR_RESULT()	while(GO == 1)

#define ADC_SELECT_CLOCK_SOURCE(clock)	(ADCS2 = ((clock) & 0x4 ) >> 2);\
										(ADCS1 = ((clock) & 0x2 ) >> 1);\
										(ADCS0 = (clock) & 0x1)

#define ADC_CONFIGURE_PORT()    PCFG3 = 0;\
                                PCFG2 = 0;\
                                PCFG1 = 1;\
                                PCFG0 = 0



void adc_init(unsigned char clk)
{
    ADC_SET_STATE(0); //ADC OFF (INITIAL STATE)
    ADC_SELECT_CLOCK_SOURCE(clk);
    ADC_SELECT_VREFP(0); //Internal VREF+
	ADC_SELECT_VREFN(0); //Internal VREF-
	ADC_CONFIGURE_PORT();
}

unsigned int adc_getResult(unsigned char channel)
{
     unsigned int result = 0;
     ADC_SET_STATE(1); //TURN ON ADC
     ADC_SELECT_CHANNEL(channel);
     ADC_SELECT_RESULT_JUSTIFICATION(1); //RIGHT JUSTIFICATION

     ADC_START_CONVERSION();
     ADC_WAIT_FOR_RESULT();
     result = ADC_READ_RESULT(1);

     ADC_SET_STATE(0); //TURN OFF ADC
     return result;
}
