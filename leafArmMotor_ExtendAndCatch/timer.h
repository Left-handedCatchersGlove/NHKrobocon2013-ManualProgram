/*
 * timer.h タイマ制御用のライブラリ
 * mega88p/mega168p向け
 *
 * namespace: Timerx
 * Created: 2012/01/04 1:32:48
 *  Author: hirokazu yokoyama
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "grip.h"

static void (*Timer0_compAMatchHandler)(void);
static void (*Timer0_compBMatchHandler)(void);
static void (*Timer0_overflowHandler)(void);
static void (*Timer1_compAMatchHandler)(void);
static void (*Timer1_compBMatchHandler)(void);
static void (*Timer1_overflowHandler)(void);
static void (*Timer1_captureHandler)(void);
static void (*Timer2_compAMatchHandler)(void);
static void (*Timer2_compBMatchHandler)(void);
static void (*Timer2_overflowHandler)(void);

/**
 * タイマのプリンスケーラ(分周比)
 */
typedef enum Timer_Prescaler {
	/** 分周なし */
	Timer_PRESCALER_NONE = 0b001,
	/** 8分周 */
    Timer_PRESCALER_8 = 0b010,               
	/** 64分周 */
    Timer_PRESCALER_64 = 0b011,              
    /** 256分周 */
	Timer_PRESCALER_256 = 0b100,             
    Timer_PRESCALER_1024 = 0b101,            // 1024分周
    Timer_PRESCALER_OUTSIDE_UNDER = 0b110,   // 外部クロック(下降)
    Timer_PRESCALER_OUTSIDE_OVER = 0b111     // 外部クロック(上昇)	
} Timer_Prescaler;

/**
 * 比較出力モード選択A
 */
typedef enum Timer_MatchModeA {
	/** 標準ポート動作(タイマ使わないよ) */
	Timer_A_NONE = 0b00,
	/** トグル出力(Low,Highを交互に出力) */
	Timer_A_TOGGLE = 0b01,
	/** 比較一致でLow, BOTTOMでHighを出力(非反転動作)[10] */
	Timer_A_LOW_AT_COMPARE_MATCH = 0b10,
	/** 比較一致でHigh, BOTTOMでLowを出力(反転動作)[11] */
	Timer_A_HIGH_AT_COMPARE_MATCH = 0b11
} Timer_MatchModeA;

/**
 * 比較出力モード選択B
 */
typedef enum Timer_MatchModeB {
	/** 標準ポート動作(タイマ使わないよ) */
	Timer_B_NONE = 0b00,
	/** 比較一致でLow, BOTTOMでHighを出力(非反転動作)[10] */
	Timer_B_LOW_AT_COMPARE_MATCH = 0b10,
	/** 比較一致でHigh, BOTTOMでLowを出力(反転動作)[11] */
	Timer_B_HIGH_AT_COMPARE_MATCH = 0b11
} Timer_MatchModeB;

/**
 * タイマ0の波形選択
 */
typedef enum Timer0_PulseMode {
	// 標準動作(タイマ使わないよ)
	Timer0_PULSE_NONE = 0b000,
	// 8bit位相基準PWM,TOP値$FF, OCR更新時:TOP, TOV0設定時:BOTTOM
	Timer0_8BIT_PHASE_BASED_PWM = 0b001,
	// 比較一致CTC動作,TOP値:OCR0A, OCR0更新時:即時, TOV0更新時:MAX
	Timer0_CTC = 0b010,
	// 8bit高速PWM動作,TOP値$FF, OCR更新時:BOTTOM, TOV0設定時:TOP
	Timer0_8BIT_FIRST_PWM = 0b011,
	// 位相基準PWM,TOP値$OCR0A, OCR更新時:TOP, TOV0設定時:BOTTOM
	Timer0_PHASE_BASED_PWM = 0b101,
	// 高速PWM, TOP値$FF, OCR更新時:BOTTOM, TOV0設定時:TOP
	Timer0_FIRST_PWM = 0b111
} Timer0_PulseMode;

/**
 * タイマ1の波形選択
 */
typedef enum Timer1_PulseMode {
	// 標準動作(タイマ使わないよ)
	Timer1_PULSE_NONE = 0b0000,
	// 8bit位相基準PWM,TOP値:$FF, OCR更新時:TOP, TOV0設定時:BOTTOM
	Timer1_8BIT_PHASE_BASED_PWM = 0b0001,
	// 9bit位相基準PWM,TOP値:$1FF, OCR更新時:TOP, TOV0設定時:BOTTOM
	Timer1_9BIT_PHASE_BASED_PWM = 0b0010,
	// 10bit位相基準PWM,TOP値:3$FF, OCR更新時:TOP, TOV0設定時:BOTTOM
	Timer1_10BIT_PHASE_BASED_PWM = 0b0011,
	// 比較一致CTC動作,TOP値:OCR1A, OCR0更新時:即時, TOV0更新時:MAX
	Timer1_CTC_OCR = 0b010,
	// 8bit高速PWM動作,TOP値:$FF, OCR更新時:BOTTOM, TOV0設定時:TOP
	Timer1_8BIT_FIRST_PWM = 0b0101,
	// 9bit高速PWM動作,TOP値:$1FF, OCR更新時:BOTTOM, TOV0設定時:TOP
	Timer1_9BIT_FIRST_PWM = 0b0110,
	// 10bit高速PWM動作,TOP値:$3FF, OCR更新時:BOTTOM, TOV0設定時:TOP
	Timer1_10BIT_FIRST_PWM = 0b0111,
	// 位相・周波数基準PWM動作,TOP値ICR1, OCR更新時:BOTTOM, TOV1設定時:BOTTOM
	Timer1_PHASE_PULSE_BASED_PWM_ICR = 0b1000,
	// 位相・周波数基準PWM動作,TOP値OCR1A, OCR更新時:BOTTOM, TOV1設定時:BOTTOM
	Timer1_PHASE_PULSE_BASED_PWM_OCR = 0b1001,
	// 位相基準PWM,TOP値$ICR1, OCR更新時:TOP, TOV0設定時:BOTTOM
	Timer1_PHASE_BASED_PWM_ICR = 0b1010,
	// 位相基準PWM,TOP値$OCR1A, OCR更新時:TOP, TOV0設定時:BOTTOM
	Timer1_PHASE_BASED_PWM_OCR = 0b1011,
	// CTC動作,TOP値:ICR1, OCR更新時:即時, TOV0設定時:MAX
	Timer1_CTC_ICR = 0b1100,
	// 高速PWM, TOP値:ICR1, OCR更新時:BOTTOM, TOV0設定時:TOP
	Timer1_FIRST_PWM_ICR = 0b1110,	
	// 高速PWM, TOP値:OCR, OCR更新時:BOTTOM, TOV0設定時:TOP
	Timer1_FIRST_PWM_OCR = 0b1111
} Timer1_PulseMode;

/**
 * タイマ2の波形選択
 */
typedef enum Timer2_PulseMode {
	// 標準動作(タイマ使わないよ)
	Timer2_PULSE_NONE = 0b000,
	// 8bit位相基準PWM,TOP値$FF, OCR更新時:TOP, TOV0設定時:BOTTOM
	Timer2_8BIT_PHASE_BASED_PWM = 0b001,
	// 比較一致CTC動作,TOP値:OCR2A, OCR0更新時:即時, TOV0更新時:MAX
	Timer2_CTC = 0b010,
	// 8bit高速PWM動作,TOP値$FF, OCR更新時:BOTTOM, TOV0設定時:TOP
	Timer2_8BIT_FIRST_PWM = 0b011,
	// 位相基準PWM,TOP値$OCR2A, OCR更新時:TOP, TOV0設定時:BOTTOM
	Timer2_PHASE_BASED_PWM = 0b101,
	// 高速PWM, TOP値$FF, OCR更新時:BOTTOM, TOV0設定時:TOP
	Timer2_FIRST_PWM = 0b111
} Timer2_PulseMode;

/**
 * タイマ0の割り込みモードの選択
 */
typedef enum Timer0_InterruptMask {
	// タイマ・カウンタ比較Aで比較一致の時に割り込みを実行する
	Timer0_INTERRUPT_MATCH_A = _BV(OCIE0A),
	// タイマ・カウンタ比較Bで比較一致の時に割り込みを実行する
	Timer0_INTERRUPT_MATCH_B = _BV(OCIE0B),
	// 溢れがおこると割り込みを実行する
	Timer0_INTERRUPT_OVERFLOW = _BV(TOIE0)
} Timer0_InterruptMask;

/**
 * タイマ1の割り込みモードの選択
 */
typedef enum Timer1_InterruptMask {
	// タイマ・カウンタ比較Aで比較一致の時に割り込みを実行する
	Timer1_INTERRUPT_MATCH_A = _BV(OCIE1A),
	// タイマ・カウンタ比較Bで比較一致の時に割り込みを実行する
	Timer1_INTERRUPT_MATCH_B = _BV(OCIE1B),
	// ICRの捕獲割り込みを実行する
	Timer1_INTERRUPT_ICR = _BV(ICIE1),
	// 溢れがおこると割り込みを実行する
	Timer1_INTERRUPT_OVERFLOW = _BV(TOIE1)
} Timer1_InterruptMask;


/**
 * タイマ2の割り込みモードの選択
 */
typedef enum Timer2_InterruptMask {
	// タイマ・カウンタ比較Aで比較一致の時に割り込みを実行する
	Timer2_INTERRUPT_MATCH_A = _BV(OCIE2A),
	// タイマ・カウンタ比較Bで比較一致の時に割り込みを実行する
	Timer2_INTERRUPT_MATCH_B = _BV(OCIE2B),
	// 溢れがおこると割り込みを実行する
	Timer2_INTERRUPT_OVERFLOW = _BV(TOIE2)
} Timer2_InterruptMask;

/**
 * タイマ・カウンタ0を初期化します。
 * matchA, matchBの値をTimer_A_NONE及びTimer_B_NONE以外を指定した場合、PD5及びPD6
 * がDDRがHighになり出力に設定されます。
 * @param matchA タイマAの比較一致時の動作を選択
 * @param matchB タイマBの比較一致次の動作を選択
 * @param wgm 出力波形,モードを選択
 * @param p プリンスケーラ(分周比)
 */
void Timer0_init(Timer_MatchModeA matchA, Timer_MatchModeB matchB,
                        Timer0_PulseMode wgm, Timer_Prescaler p) {    							
	TCCR0A = (matchA << 6) | (matchB << 4) | (wgm & 0b0011);
	TCCR0B = ((wgm & 0b0100) << 1) | p;
	if(matchA != Timer_A_NONE) {
		DDRD |= _BV(PD6);
	}
	if(matchB != Timer_B_NONE) {
		DDRD |= _BV(PD5);
	}
}

/**
 * タイマ・カウンタ1を初期化します。
 * matchA, matchBの値をTimer_A_NONE及びTimer_B_NONE以外を指定した場合、PB0及びPB1
 * がDDRがHighになり出力に設定されます。
 * @param matchA タイマAの比較一致時の動作を選択
 * @param matchB タイマBの比較一致次の動作を選択
 * @param wgm 出力波形,モードを選択
 * @param p プリンスケーラ(分周比)
 */
void Timer1_init(Timer_MatchModeA matchA, Timer_MatchModeB matchB,
                        Timer1_PulseMode wgm, Timer_Prescaler p) {    							
	TCCR1A = (matchA << 6) | (matchB << 4) | (wgm & 0b0011);
	TCCR1B = ((wgm & 0b1100) << 1) | p;
	if(matchA != Timer_A_NONE) {
		DDRB |= _BV(PB1);
	}
	if(matchB != Timer_B_NONE) {
		DDRB |= _BV(PB2);
	}
}

/**
 * タイマ・カウンタ2を初期化します。
 * matchA, matchBの値をTimer_A_NONE及びTimer_B_NONE以外を指定した場合、PB3及びPB4
 * がDDRがHighになり出力に設定されます。
 * @param matchA タイマAの比較一致時の動作を選択
 * @param matchB タイマBの比較一致次の動作を選択
 * @param wgm 出力波形,モードを選択
 * @param p プリンスケーラ(分周比)
 */
void Timer2_init(Timer_MatchModeA matchA, Timer_MatchModeB matchB,
                        Timer2_PulseMode wgm, Timer_Prescaler p) {    							
	TCCR2A = (matchA << 6) | (matchB << 4) | (wgm & 0b0011);
	TCCR2B = ((wgm & 0b0100) << 1) | p;
	if(matchA != Timer_A_NONE) {
		DDRB |= _BV(PB3);
	}
	if(matchB != Timer_B_NONE) {
		DDRD |= _BV(PD3);
	}
}
	
/**
 * タイマ0の割り込みを許可します
 * @param mask 割り込みのタイミングを選択
 */	
void Timer0_setTimerInterruptEnable(Timer0_InterruptMask mask) {
	TIMSK0 = mask;
}

/**
 * タイマ1の割り込みを許可します
 * @param mask 割り込みのタイミングを選択
 */	
void Timer1_setTimerInterruptEnable(Timer1_InterruptMask mask) {
	TIMSK1 = mask;
}

/**
 * タイマ2の割り込みを許可します
 * @param mask 割り込みのタイミングを選択
 */	
void Timer2_setTimerInterruptEnable(Timer2_InterruptMask mask) {
	TIMSK2 = mask;
}

/**
 * TCNT0 に設定するカウント値を指定します。
 * @param count カウンタ値
 */		
void Timer0_setTimerCounter(uint8_t count) {
	TCNT0 = count;
}

/**
 * TCNT1 に設定するカウント値を指定します。
 * @param count カウンタ値
 */
void Timer1_setTimerCounter(uint16_t count) {
	TCNT1 = count;
}	

/**
 * TCNT2 に設定するカウント値を指定します。
 * @param count カウンタ値
 */
void Timer2_setTimerCounter(uint8_t count) {
	TCNT2 = count;
}

/**
 * タイマ0Aの比較一致の基準値を指定します。OCR0Aの値を設定します
 * @param criteriaValue OCR0Aに代入する値
 */
void Timer0_setTimerACriteria(uint8_t criteriaValue) {
	OCR0A = criteriaValue;
}

/**
 * タイマ0Bの比較一致の基準値を指定します。OCR0Bの値を設定します
 * @param criteriaValue OCR0Bに代入する値
 */
void Timer0_setTimerBCriteria(uint8_t criteriaValue) {
	OCR0B = criteriaValue;
}

/**
 * タイマ1Aの比較一致の基準値を指定します。OCR1Aの値を設定します
 * @param criteriaValue OCR1Aに代入する値
 */
void Timer1_setTimerACriteria(uint16_t criteriaValue) {
	OCR1AH = (criteriaValue >> 8) &0x00FF;
	OCR1AL = criteriaValue &0x00FF;
}

/**
 * タイマ1Bの比較一致の基準値を指定します。OCR1Bの値を設定します
 * @param criteriaValue OCR1Bに代入する値
 */
void Timer1_setTimerBCriteria(uint16_t criteriaValue) {
	OCR1BH = (criteriaValue >> 8) &0x00FF;
	OCR1BL = criteriaValue &0x00FF;
}

/**
 * タイマ1の捕獲割り込みの基準値を指定します。ICR1の値を指定します
 */
void Timer1_setTimerCaptureCriteria(uint16_t criteriaValue) {
	ICR1 = criteriaValue;
}

/**
 * タイマ2Aの比較一致の基準値を指定します。OCR2Aの値を設定します
 * @param criteriaValue OCR2Aに代入する値
 */
void Timer2_setTimerACriteria(uint8_t criteriaValue) {
	OCR2A = criteriaValue;
}

/**
 * タイマ2Bの比較一致の基準値を指定します。OCR2Bの値を設定します
 * @param criteriaValue OCR2Bに代入する値
 */
void Timer2_setTimerBCriteria(uint8_t criteriaValue) {
	OCR2B = criteriaValue;
}

/**
 * オーバーフロー時の割り込みハンドラを設定します
 * @param func ハンドラ関数のポインタ
 */
void Timer0_setOverflowHandler(void (*func)(void)) {
	Timer0_overflowHandler = func;
}

/**
 * タイマA時の割り込みハンドラを設定します
 * @param func ハンドラ関数のポインタ
 */
void Timer0_setMatchAHandler(void (*func)(void)) {
	Timer0_compAMatchHandler = func;
}

/**
 * オーバーフロー時の割り込みハンドラを設定します
 * @param func ハンドラ関数のポインタ
 */
void Timer0_setMatchBHandler(void (*func)(void)) {
	Timer0_compBMatchHandler = func;
}

/**
 * オーバーフロー時の割り込みハンドラを設定します
 * @param func ハンドラ関数のポインタ
 */
void Timer1_setOverflowHandler(void (*func)(void)) {
	Timer1_overflowHandler = func;
}

/**
 * タイマA時の割り込みハンドラを設定します
 * @param func ハンドラ関数のポインタ
 */
void Timer1_setMatchAHandler(void (*func)(void)) {
	Timer1_compAMatchHandler = func;
}

/**
 * オーバーフロー時の割り込みハンドラを設定します
 * @param func ハンドラ関数のポインタ
 */
void Timer1_setMatchBHandler(void (*func)(void)) {
	Timer1_compBMatchHandler = func;
}

/**
 *  捕獲割り込みのハンドラを設定します。
 * @aram func ハンドラ関数のポインタ
 */
void Timer1_setCaptureHandler(void (*func)(void)) {
	Timer1_captureHandler = func;
}

/**
 * オーバーフロー時の割り込みハンドラを設定します
 * @param func ハンドラ関数のポインタ
 */
void Timer2_setOverflowHandler(void (*func)(void)) {
	Timer2_overflowHandler = func;
}

/**
 * タイマA時の割り込みハンドラを設定します
 * @param func ハンドラ関数のポインタ
 */
void Timer2_setMatchAHandler(void (*func)(void)) {
	Timer2_compAMatchHandler = func;
}

/**
 * オーバーフロー時の割り込みハンドラを設定します
 * @param func ハンドラ関数のポインタ
 */
void Timer2_setMatchBHandler(void (*func)(void)) {
	Timer2_compBMatchHandler = func;
}

ISR(TIMER0_OVF_vect) {
	Timer0_overflowHandler();
}

ISR(TIMER0_COMPA_vect) {
	Timer0_compAMatchHandler();
}

ISR(TIMER0_COMPB_vect) {
	Timer0_compBMatchHandler();
}

ISR(TIMER1_OVF_vect) {
	Timer1_overflowHandler();
}
ISR(TIMER1_COMPA_vect) {
	Timer1_compAMatchHandler();
}
ISR(TIMER1_COMPB_vect) {
	Timer1_compBMatchHandler();
}
ISR(TIMER1_CAPT_vect) {
	Timer1_captureHandler();
}
	
ISR(TIMER2_OVF_vect) {
	Timer2_overflowHandler();
}

ISR(TIMER2_COMPA_vect) {
	Timer2_compAMatchHandler();
}

ISR(TIMER2_COMPB_vect) {
	Timer2_compBMatchHandler();
}
	
#endif /* TIMER_H_ */