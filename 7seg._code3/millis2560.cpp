#include "millis2560.h"

// 프로그램 시작 이후의 경과 시간
volatile unsigned long timer0_millis = 0;
volatile int timer0_micros = 0;

ISR(TIMER0_OVF_vect) {
	unsigned long m = timer0_millis;
	int f = timer0_micros;

	m += MILLIS_INCREMENT_PER_OVERFLOW; // 밀리초 단위 시간 증가
	f += MICROS_INCREMENT_PER_OVERFLOW; // 마이크로초 단위 시간 증가

	// 마이크로초가 1000을 넘어가면 밀리초를 증가
	m += (f / 1000);
	f = f % 1000;

	timer0_millis = m;
	timer0_micros = f;
}

unsigned long millis2560() {
	unsigned long m;
	uint8_t oldSREG = SREG;   // 상태 레지스터 값 저장

	// timer0_millis 값을 읽는 동안
	// timer0_millis 값이 변하지 않도록 인터럽트를 비활성화
	cli();

	m = timer0_millis;

	// 이전 상태 레지스터 값 복원
	// millis 함수 호출 이전에 인터럽트 허용 상태였으면 허용 상태로 복원됨
	SREG = oldSREG;

	return m;         // 프로그램 시작 후 경과 시간
}

void millis2560_init() {      // 타이머/카운터 0 설정
	TCCR0B |= (1 << CS01) | (1 << CS00);  // 분주비를 64로 설정
	TIMSK0 |= (1 << TOIE0);   // 오버플로 인터럽트 허용
	sei();              // 전역적으로 인터럽트 허용
}
