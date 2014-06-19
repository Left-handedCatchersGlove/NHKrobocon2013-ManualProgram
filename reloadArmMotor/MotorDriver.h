/** モータドライバ用のライブラリ
 * MotorDriver.h
 *
 * namespace: MotorDriver
 * Created: 2012/01/08 15:06:10
 *  Author: hirokazu
 */ 


#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_

#include <avr/io.h>
#include "grip.h"
#include "timer.h"

static const int MotorDriver_STOP = 255;

/**
 * タイマ・カウンタ0をモータドライバのPWM初期化
 * 比較値一致でLow, 8bit高速PWM,プリンスケーラ8分周
 */
void MotorDriver_init0() {
	Timer0_setTimerACriteria(MotorDriver_STOP);
	Timer0_setTimerBCriteria(MotorDriver_STOP);
	Timer0_init(Timer_A_HIGH_AT_COMPARE_MATCH, Timer_B_HIGH_AT_COMPARE_MATCH, Timer0_8BIT_FIRST_PWM, Timer_PRESCALER_8);	
}

/**
 * タイマ・カウンタ1をモータドライバのPWM初期化
 * 比較値一致でLow, 8bit高速PWM,プリンスケーラ8分周 
 */
void MotorDriver_init1() {
	Timer1_setTimerACriteria(MotorDriver_STOP);
	Timer1_setTimerBCriteria(MotorDriver_STOP);
	Timer1_init(Timer_A_HIGH_AT_COMPARE_MATCH, Timer_B_HIGH_AT_COMPARE_MATCH, Timer1_8BIT_FIRST_PWM, Timer_PRESCALER_8);
}

/**
 * タイマ・カウンタ2をモータドライバのPWM初期化
 * 比較値一致でLow, 8bit高速PWM,プリンスケーラ8分周
 */
void MotorDriver_init2() {
	Timer2_setTimerACriteria(MotorDriver_STOP);
	Timer2_setTimerBCriteria(MotorDriver_STOP);
	Timer2_init(Timer_A_HIGH_AT_COMPARE_MATCH, Timer_B_HIGH_AT_COMPARE_MATCH, Timer2_8BIT_FIRST_PWM, Timer_PRESCALER_8);
}


/**
 * タイマ・カウンタ0のモータの速さを指定します。
 * @param motorSignal モータ向け信号
 */
void MotorDriver_run0(MotorSignal motorSignal) {
	unsigned char duty = 255 - (motorSignal.speed * 2);
	if(duty > 255) {
	    duty = 255;
	}
	if(motorSignal.direction == FORWARD) {
		Timer0_setTimerACriteria(duty);
		Timer0_setTimerBCriteria(MotorDriver_STOP);
	} else if(motorSignal.direction == BACKWARD) {
		Timer0_setTimerBCriteria(duty);
		Timer0_setTimerACriteria(MotorDriver_STOP);
	}
}

/**
 * タイマ・カウンタ1のモータの速さを指定します。
 * @param motorSignal モータ向け信号
 */
void MotorDriver_run1(MotorSignal motorSignal) {
	unsigned char duty = 255 - (motorSignal.speed * 2);
	if(duty > 255) {
	    duty = 255;
	}
	if(motorSignal.direction == FORWARD) {
		Timer1_setTimerACriteria(duty);
		Timer1_setTimerBCriteria(MotorDriver_STOP);
	} else if(motorSignal.direction == BACKWARD) {
		Timer1_setTimerBCriteria(duty);
		Timer1_setTimerACriteria(MotorDriver_STOP);
	}
}


#endif /* MOTORDRIVER_H_ */