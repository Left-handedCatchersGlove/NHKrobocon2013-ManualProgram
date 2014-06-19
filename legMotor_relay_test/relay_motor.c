/*
 * relay_motor.c
 *
 * Created: 2013/03/24 23:18:06
 *  Author: Chelly
 */ 
#include <avr/io.h>
#include "relay_motor.h"
#include "grip.h"

//�O���[�o���ϐ��̏�����
int target_spd_a = 0, target_spd_b = 0;
void ( * motor_a_func_p )(void) = set_motor_a;
void ( * motor_b_func_p )(void) = set_motor_b;

/**
 *@brief PWM�Ɋւ��Ă̏������֐�
 */
void timer_pwm_init(void) {
	OCR1A = 0xFF;
	OCR0B = 0xFF;
	TCCR1A = 0xF1;
	TCCR1B = 0x0A;
}

/**
 *@brief ���o�͂Ɋւ��Ă̏������֐�
 */
void io_init(void) {
	PORTB = 0x00;
	DDRB = 0x1E;
}

/**
 *@brief �^�C�}�[�Ɋւ��Ă̏������֐�
 */
void timer0_init(void) {
	TCCR0B = 0x03;
	TIMSK0 = 0x01;
}

/**
 *@brief �����̐�Βl��Ԃ��֐�
 *@param targe�F��肽���l
 *@return ��Βl
 */
int absolute(int target) {
	if( target >= 0 )
	  return target;
	else if( target < 0 )
	  return -target;
}

int check_sign( int * i ) {
  if( *i >= 0 ){
		return 1;   // + �̕����̎�  1 ��Ԃ�
	}
	else{
		return -1;  // - �̕����̎� -1 ��Ԃ�
	}
}

void startMotorFunc(void) {
	motor_a_func_p();
	motor_b_func_p();
}

/**
 *@brief A���[�^�̃X�s�[�h�Ɋւ��Ă̊֐�
 *@param speed�F�X�s�[�h���󂯎��
 */
void setSpeedMotorA(int a_speed) {
	int speed;
	speed = absolute(a_speed);
	if( speed > 255 ) speed = 255;
	
	OCR1A = 255 - speed;
}

/**
 *@brief A���[�^�̉�]������ς���
 */
void chenge_direction_a(void) {
	PORTB ^= 0x08;
}

/**
 *@brief A���[�^�̃��C���֐�
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
 *@brief A���[�^���I�t�ɂ���
 */
void set_off_motor_a(void) {
	OCR1A = 255;
}

/**
 *@brief B���[�^�̃X�s�[�h�Ɋւ��Ă̊֐�
 *@param speed�F�X�s�[�h���󂯎��
 */
void setSpeedMotorB(int b_speed) {
	int speed;
	speed = absolute(b_speed);
	if( speed > 255 ) speed = 255;
	
	OCR1B = 255 - speed;
}

/**
 *@brief B���[�^�̉�]������ς���
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
 *@brief B���[�^���I�t�ɂ���
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