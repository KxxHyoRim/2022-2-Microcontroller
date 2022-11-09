#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"

#define set_bit(value, bit) ( _SFR_BYTE(value) |= _BV(bit) )
#define clear_bit(value, bit) ( _SFR_BYTE(value) &= ~_BV(bit) )

void PORT_init() {
  set_bit(DDRE, 4);       // 아두이노 2번
  set_bit(DDRE, 5);       // 아두이노 3번
  set_bit(DDRG, 5);       // 아두이노 4번
  set_bit(DDRE, 3);       // 아두이노 5번
}

int main(void) {

  ADC_init(0);        // AD 변환기 초기화
  PORT_init();        // LED 연결 핀을 출력으로 설정

  while (1) {
    int read = read_ADC();    // 가변저항 읽기
    int count = (read >> 8) + 1;

    switch (count) {    // LED 개수에 따라 LED 점멸
      case 1:
        set_bit(PORTE, 4);
        clear_bit(PORTE, 5);
        clear_bit(PORTG, 5);
        clear_bit(PORTE, 3);
        break;
      case 2:
        set_bit(PORTE, 4);
        set_bit(PORTE, 5);
        clear_bit(PORTG, 5);
        clear_bit(PORTE, 3);
        break;
      case 3:
        set_bit(PORTE, 4);
        set_bit(PORTE, 5);
        set_bit(PORTG, 5);
        clear_bit(PORTE, 3);
        break;
      case 4:
        set_bit(PORTE, 4);
        set_bit(PORTE, 5);
        set_bit(PORTG, 5);
        set_bit(PORTE, 3);
        break;
    }

    _delay_ms(100);      // 1초에 한 번 읽음
  }

  return 0;
}
