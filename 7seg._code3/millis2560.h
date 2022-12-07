#ifndef _MILLIS2560_
#define _MILLIS2560_

#include <avr/io.h>
#include <avr/interrupt.h>

#define MILLIS_INCREMENT_PER_OVERFLOW  1
#define MICROS_INCREMENT_PER_OVERFLOW 24

unsigned long millis2560();
void millis2560_init();

#endif
