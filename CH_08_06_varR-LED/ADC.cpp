#include "ADC.h"

int MODE = FREE_RUNNING;

void ADC_init(unsigned char channel, int mode = FREE_RUNNING){
	MODE = mode;
	
	ADMUX |= (1 << REFS0);		// AVCC를 기준 전압으로 선택
	// 채널 선택. 8~15번 채널은 ADMUX 이외에 ADCSRB 레지스터 설정 필요
	ADMUX = ((ADMUX & 0xE0) | (channel & 0x07));	
	if(channel > 7) ADCSRB |= (1 << MUX5);

	// 분주비를 128로 설정
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
	
	ADCSRA |= (1 << ADEN);		// ADC 활성화
	
	if(MODE == FREE_RUNNING){
		ADCSRA |= (1 << ADATE);		// 자동 트리거 모드 활성화

		// 프리러닝 모드 선택
		ADCSRB &= ~(1 << ADTS2) & ~(1 << ADTS1) & ~(1 << ADTS0);
		
		ADCSRA |= (1 << ADSC);		// 변환 시작
	}
}

int read_ADC(void){
	if(MODE == SINGLE_CONVERSION){
		ADCSRA |= (1 << ADSC);		// 변환 시작
	}
	
	while(!(ADCSRA & (1 << ADIF)));	// 변환 종료 대기

	return ADC;				// 10비트 값을 반환
}
