#ifndef _ADC_
#define _ADC_

#include <avr/io.h>
#include <avr/interrupt.h>

#define FREE_RUNNING		1
#define SINGLE_CONVERSION 	2

void ADC_init(unsigned char channel, int mode = FREE_RUNNING);
int read_ADC(void);

#endif
