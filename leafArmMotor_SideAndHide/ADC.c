/*
 * ADC.c
 *
 * Created: 2013/02/27 22:23:38
 *  Author: kubrick
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"

void initADC(uint8_t ADPIN) {
	DDRC &= (~ADPIN);
	ADMUX = ADPC0;
	ADCSRA = 0x81;
	_delay_ms(100);
}

int startADC(uint8_t ADPIN) {
	ADMUX = ADPIN;
	ADCSRA |= 0x40;
	while(ADCSRA & 0x40)
	return (int)ADC;
}