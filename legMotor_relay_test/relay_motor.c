/*
 * relay_motor.c
 *
 * Created: 2013/03/24 23:18:06
 *  Author: Chelly
 */ 
#include <avr/io.h>
#include "relay_motor.h"
#include "grip.h"

//グローバル変数の初期化
int target_spd_a = 0, target_spd_b = 0;
void ( * motor_a_func_p )(void) = set_motor_a;
void ( * motor_b_func_p )(void) = set_motor_b;

/**
 *@brief PWMに関しての初期化関数
 */
void timer_pwm_init(void) {
	OCR1A = 0xFF;
	OCR0B = 0xFF;
	TCCR1A = 0xF1;
	TCCR1B = 0x0A;
}

/**
 *@brief 入出力に関しての初期化関数
 */
void io_init(void) {
	PORTB = 0x00;
	DDRB = 0x1E;
}

/**
 *@brief タイマーに関しての初期化関数
 */
void timer0_init(void) {
	TCCR0B = 0x03;
	TIMSK0 = 0x01;
}

/**
 *@brief 引数の絶対値を返す関数
 *@param targe：取りたい値
 *@return 絶対値
 */
int absolute(int target) {
	if( target >= 0 )
	  return target;
	else if( target < 0 )
	  return -target;
}

int check_sign( int * i ) {
  if( *i >= 0 ){
		return 1;   // + の符号の時  1 を返す
	}
	else{
		return -1;  // - の符号の時 -1 を返す
	}
}

void startMotorFunc(void) {
	motor_a_func_p();
	motor_b_func_p();
}

/**
 *@brief Aモータのスピードに関しての関数
 *@param speed：スピードを受け取る
 */
void setSpeedMotorA(int a_speed) {
	int speed;
	speed = absolute(a_speed);
	if( speed > 255 ) speed = 255;
	
	OCR1A = 255 - speed;
}

/**
 *@brief Aモータの回転方向を変える
 */
void chenge_direction_a(void) {
	PORTB ^= 0x08;
}

/**
 *@brief Aモータのメイン関数
 */
void set_motor_a(void) {
	static int now_speed = 0;
	static int next_speed = 0;
	
	if( next_speed < target_spd_a )
	  next_speed = limit( now_speed + CHANGE, -( 255 / 2 ), target_spd_a );
	else if( next_speed > target_spd_a )
	  next_speed = limit( now_speed - CHANGE, target_spd_a, ( 255 / 2 ) );
	
	if( check_sign( &now_speed ) != check_sign( &next_speed ) ) {
		set_off_motor_a();
		chenge_direction_a();
		now_speed = next_speed;
		motor_a_func_p = wait_motor_a_chatterring;
	}
	else {
		now_speed = next_speed;
		setSpeedMotorA( now_speed * 2 );
	}
}

/**
 *@brief Aモータをオフにする
 */
void set_off_motor_a(void) {
	OCR1A = 255;
}

/**
 *@brief Bモータのスピードに関しての関数
 *@param speed：スピードを受け取る
 */
void setSpeedMotorB(int b_speed) {
	int speed;
	speed = absolute(b_speed);
	if( speed > 255 ) speed = 255;
	
	OCR1B = 255 - speed;
}

/**
 *@brief Bモータの回転方向を変える
 */
void chenge_direction_b(void) {
	PORTB ^= 0x10;
}

void set_motor_b(void) {
	static int nowspeed = 0;
	static int nextspeed = 0;
	
	if( nextspeed < target_spd_b )
		nextspeed = limit( nowspeed + CHANGE, -( 255 / 2 ), target_spd_b );
	else if(nextspeed > target_spd_b)
		nextspeed = limit( nowspeed - CHANGE, target_spd_b, ( 255 / 2 ) );
  
  if( check_sign( nowspeed ) != check_sign( nextspeed ) ){
	  set_off_motor_b();
	  chenge_direction_b();
	  nowspeed = nextspeed;
    motor_b_func_p = wait_motor_b_chatterring;
  }
  else{
    nowspeed = nextspeed;
	  setSpeedMotorB( nowspeed * 2 );
  }
}

/**
 *@brief Bモータをオフにする
 */
void set_off_motor_b(void) {
	OCR1B = 255;
}

void setTargetSpeed( int a, int b ) {
	target_spd_a = a;
	target_spd_b = b;
}

void wait_motor_a_chatterring(void) {
	static int count = 0;
	
	if( count < WAIT_RELAY ) count++;
	else {
		count = 0;
		motor_a_func_p = set_off_motor_a;
	}
}

void wait_motor_b_chatterring(void) {
	static int count = 0;
	
	if( count < WAIT_RELAY ) count++;
	else {
		count = 0;
		motor_b_func_p = set_off_motor_b;
	}
}