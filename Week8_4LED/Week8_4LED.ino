#define F_CPU 16000000L 
#include<avr/io.h> 
#include<util/delay.h>

#define set_bit(value, bit) (_SFR_BYTE(value) |= _BV(bit)) 
#define clear_bit(value, bit)(_SFR_BYTE(value) &= ~_BV(bit))

int main(void) {
  DDRE |= 0x38;
  DDRG |= 0x20;
  int pattern = 0;
  while (1) {
    show_pattern(pattern);
    pattern = (pattern + 1) % 4;
    _delay_ms(1000);
  }
  return 0;
}

void show_pattern(int pattern) {
  switch (pattern) {
    case 0:
set_bit(PORTE, 4); clear_bit(PORTE, 5); clear_bit(PORTG, 5); clear_bit(PORTE, 3); break;
case 1: clear_bit(PORTE, 4); set_bit(PORTE, 5); clear_bit(PORTG, 5); clear_bit(PORTE, 3); break;
case 2: clear_bit(PORTE, 4); clear_bit(PORTE, 5); set_bit(PORTG, 5); clear_bit(PORTE, 3); break;
    case 3:
      clear_bit(PORTE, 4);
      clear_bit(PORTE, 5);
      clear_bit(PORTG, 5);
      set_bit(PORTE, 3);
      break;
} }