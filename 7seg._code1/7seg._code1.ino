#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

// 0에서 9까지 숫자 표현을 위한 세그먼트 dp, g, f, e, d, c, b, a 값
uint8_t patterns[] = 
{0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};

void select_digit(int digit) {
  // 선택된 자리만 논리 0을 가하고 나머지에는 논리 1을 가함
  // 왼쪽부터 digit 1(PK4)에서 digit 4(PK7)로 증가
  PORTK |= 0xF0;      // 논리 1 출력으로 모든 자리 선택 해제
  PORTK &= ~(0x01 << (3 + digit));  // 선택한 자리만 논리 0 출력
}

void show_number(int no) {
  uint8_t upper = patterns[no] & 0xF0; // 숫자의 상위 4bit분리 
  uint8_t lower = patterns[no] & 0x0F; // 숫자의 하위 4bit분리 

  PORTF = (PORTF & 0x0F) | (lower << 4);  // d, c, b, a 세그먼트
  PORTK = (PORTK & 0xF0) | (upper >> 4);  // dp, g, f, e 세그먼트
}

int main(void) {
  DDRF |= 0xF0;
  DDRK = 0xFF;    // 12개 핀을 출력으로 설정

  while (1) {
    for (int digit = 1; digit <= 4; digit++) {
      select_digit(digit);      // 자리 선택
      for (int no = 0; no < 10; no++) {
        show_number(no);    // 숫자 출력
        _delay_ms(200);
      }
    }
  }

  return 0;
}
