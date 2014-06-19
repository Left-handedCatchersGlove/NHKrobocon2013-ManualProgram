/*
 * Hbridge.c
 *
 * Created: 2013/02/25 22:17:30
 *  Author: kubrick
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "hBridge.h"

void initHbridge(void) {
	// 出力設定
	DDRD = 0xFF;
	DDRB = 0xFF;
	// ポート初期化
	PORTD = D_FREE;
	PORTB = B_FREE;
	
	TCCR0A = FREE; // PWM出力停止
	TCCR0B = 0x02; // Dポートの周期設定
	
	TCCR2A = FREE; // PWM出力停止
	TCCR2B = 0x20; // Bポートの周期設定
	
	OCR0A = 0;
	OCR0B = 0; // Dポート出力比
	OCR2A = 0;
	OCR2B = 0; // Bポート出力比
}

void D_pwmControl(uint8_t direction, uint8_t speed) {
	if( pre_Dinput == direction ) { // 前回の入力と回転方向が同じ
	  // speedに応じた回転速度
		OCR0A = speed;
		OCR0B = speed;
	}		
	else { // 回転方向が変わるとき
		pre_Dinput = direction;            // 今回の入力を記録
		D_portDirectionChange(&direction); // 回転方向の変化
		// speedに応じた回転速度
		OCR0A = speed;
		OCR0B = speed;
	}
}

void D_portDirectionChange(uint8_t * direction) {
	OCR0A  = 0;
	OCR0B  = 0; // PWM比を0にする
	TCCR0A = FREE;      // PWMをオフ
	PORTD  = D_FREE;    // ポート初期化
	
	switch( *(direction) ) { // 回転方向各種
		default:
		case 0x00:
		  PORTD  = D_FREE;
		  TCCR0A = FREE;
		  break;
		case 0x01:
		  PORTD  = D_STOP;
		  TCCR0A = MYSTOP;
		  break;
		case 0x02:
		  PORTD  = D_ADVANCE;
		  TCCR0A = ADVANCE;
		  break;
		case 0x03:
		  PORTD  = D_RETREAT;
		  TCCR0A = RETREAT;
		  break;
	}
}

void B_pwmControl(uint8_t direction, uint8_t speed) {
	if( pre_Binput == direction ) {
		// speedに応じた回転速度
		OCR2A = speed;
		OCR2B = speed;
	}		
	else {
		pre_Binput = direction;
		B_portDirectionChange(&direction);
		OCR2A = speed;
		OCR2B = speed;
	}
}

void B_portDirectionChange(uint8_t * direction) {
	OCR2A  = 0;
	OCR2B = 0; // PWM比を0にする
	TCCR2A = FREE;      // PWMをオフ
	PORTB  = B_FREE;    // ポート初期化
	
	switch( *(direction) ) { // 回転方向各種
		default:
		case 0x00:
		  PORTB  = B_FREE;
		  TCCR2A = FREE;
		  break;
		case 0x01:
		  PORTB  = B_STOP;
		  TCCR2A = MYSTOP;
		  break;
		case 0x02:
		  PORTB  = B_ADVANCE;
		  TCCR2A = ADVANCE;
		  break;
		case 0x03:
		  PORTB  = B_RETREAT;
		  TCCR2A = RETREAT;
		  break;
	} 
}