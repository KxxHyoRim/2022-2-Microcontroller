#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define set_bit(value, bit) (_SFR_BYTE(value) |= _BV(bit))
#define clear_bit(value, bit) (_SFR_BYTE(value) &= ~_BV(bit))

int main(void) {
  init();
  Serial.begin(9600);

  uint8_t prev = 0, curr = 0;
  int pattern = 0;

  DDRJ &= ~0x01;
  DDRE |= 0x38;
  DDRG |= 0x20;

  while (1) {


    curr = PINJ & 0x01;  // 버튼 상태 읽기
    if (isButtonPressed(curr, prev)) {
      show_pattern(pattern);
      ++pattern %= 4;
    }

    Serial.println(curr);
    Serial.println(prev);
    Serial.println("==========");
    
    prev = curr;
  }
  return 0;
}

bool isButtonPressed(int curr, int prev) {
  return curr && !prev;
}

void show_pattern(int pattern) {
  switch (pattern) {
    case 0:
      set_bit(PORTE, 4);
      clear_bit(PORTE, 5);
      clear_bit(PORTG, 5);
      clear_bit(PORTE, 3);
      break;
    case 1:
      clear_bit(PORTE, 4);
      set_bit(PORTE, 5);
      clear_bit(PORTG, 5);
      clear_bit(PORTE, 3);
      break;
    case 2:
      clear_bit(PORTE, 4);
      clear_bit(PORTE, 5);
      set_bit(PORTG, 5);
      clear_bit(PORTE, 3);
      break;
    case 3:
      clear_bit(PORTE, 4);
      clear_bit(PORTE, 5);
      clear_bit(PORTG, 5);
      set_bit(PORTE, 3);
      break;
  }
}