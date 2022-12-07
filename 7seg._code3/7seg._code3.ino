#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "millis2560.h"

#define SEGMENT_DELAY 5    // LED가 완전히 켜지기 위한 시간

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
  uint8_t upper = patterns[no] & 0xF0;
  uint8_t lower = patterns[no] & 0x0F;

  PORTF = (PORTF & 0x0F) | (lower << 4);  // d, c, b, a 세그먼트
  PORTK = (PORTK & 0xF0) | (upper >> 4);  // dp, g, f, e 세그먼트
}

void display_4digit_number(int no) {
  int thousands = no / 1000;      // 천의 자리
  int hundreds = no / 100 % 10;  // 백의 자리
  int tens = no / 10 % 10;       // 십의 자리
  int ones = no % 10;           // 일의 자리

  select_digit(1);
  show_number(thousands);
  _delay_ms(SEGMENT_DELAY);
 
  select_digit(2);
  show_number(hundreds);
  _delay_ms(SEGMENT_DELAY);
 
  select_digit(3);
  show_number(tens);
  _delay_ms(SEGMENT_DELAY);
 
  select_digit(4);
  show_number(ones);
  _delay_ms(SEGMENT_DELAY);
}

int main(void) {
  DDRF |= 0xF0;
  DDRK = 0xFF;     // 12개 핀을 출력으로 설정

  millis2560_init();  // 타이머/카운터0 설정 (초기화)
                     // 분주비-64, overflow I 허용, global I 허용

  unsigned long time_p = millis2560(), time_c;
  int minutes = 0, seconds = 0;   // 분, 초

  while (1) {
    time_c = millis2560();  // program 시작 후 경과시간 저장 

    if (time_c - time_p >= 1000) {  // 1초 경과 시 분, 초 계산
      time_p = time_c;
      seconds++;
      minutes += (seconds / 60);
      seconds %= 60;
      minutes %= 60;
    }
    // 4자리 숫자를 4자리 7세그먼트 표시장치에 표시
    display_4digit_number(minutes * 100 + seconds);
  }
  return 0;
}
