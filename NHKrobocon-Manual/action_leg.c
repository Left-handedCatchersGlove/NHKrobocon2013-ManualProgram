/*
 * action_leg.c
 *
 * Created: 2013/02/22 17:03:18
 *  Author: kubrick
 */ 
#include <avr/io.h>
#include "motor_structure.h"
#include "connect.h"
#include "action_leg.h"

volatile uint8_t speed = 0;

/**
*@brief �O�i����(�J�[�u����)
 *@param Allmotorstatus * motordata
 */
void front_legmotor( AllMotorStatus * motordata, uint8_t rudder, char legFlg ){
  uint8_t speed = 0;
  motordata -> leg_motor_left.direction = FORWARD;
  motordata -> leg_motor_right.direction = FORWARD;
  
  if( legFlg == 0 ) {
    if( 117 < rudder && rudder < 137 ) { // ���i����
      motordata -> leg_motor_left.speed  = MAX_SPEED;
      motordata -> leg_motor_right.speed = MAX_SPEED;
    }
    else if( rudder <= 117 ) { // ���J�[�u����
      motordata -> leg_motor_right.speed = MAX_SPEED;
      speed = (uint8_t)( (float)( ( ( 107.0 / 117.0 ) * rudder ) + LOW_SPEED ) );
      motordata -> leg_motor_left.speed = speed;
    }
    else if( rudder >= 137 ) { // �E�J�[�u����
      motordata -> leg_motor_left.speed = MAX_SPEED;
      speed = (uint8_t)( (float)( rudder * (- 107.0 / 118.0 )) + ( 29645.0 / 118.0 ) );
      motordata -> leg_motor_right.speed = speed;
    }
  }
  else if( legFlg == 1 ) {
    motordata -> leg_motor_left.speed  = LOW_SPEED;
    motordata -> leg_motor_right.speed = LOW_SPEED;
  }
  
  motordata -> leg_motor_left.speed  = limit( MAX_SPEED, LOW_SPEED, motordata -> leg_motor_left.speed );
  motordata -> leg_motor_right.speed = limit( MAX_SPEED, LOW_SPEED, motordata -> leg_motor_right.speed );
}

/**
 *@brief �O�i�֐�(�J�[�u�Ȃ�)
 *@param AllmototStatus * motordata �\���̂̃|�C���^
 */
void leg_motor_Prototype( AllMotorStatus * motordata, char legFlg ) {
  motordata -> leg_motor_left.direction  = FORWARD;
  motordata -> leg_motor_right.direction = FORWARD;
  
  // �������[�h
  if( !legFlg ) {
	  if( speed >= MAX_SPEED ) {
		  motordata -> leg_motor_left.speed  = MAX_SPEED;
      motordata -> leg_motor_right.speed = MAX_SPEED;
	  
	    motordata -> leg_motor_left.speed  = limit( MAX_SPEED, LOW_SPEED, motordata -> leg_motor_left.speed );
		  motordata -> leg_motor_right.speed = limit( MAX_SPEED, LOW_SPEED, motordata -> leg_motor_right.speed );
	  }
	  else {
		  speed+=4;
		  motordata -> leg_motor_left.speed  = speed;
		  motordata -> leg_motor_right.speed = speed;
	  }
  }
  // �ᑬ���[�h
  else {
	  if( speed >= LOW_SPEED ) {
      motordata -> leg_motor_left.speed  = LOW_SPEED;
      motordata -> leg_motor_right.speed = LOW_SPEED;
	  
	    motordata -> leg_motor_left.speed  = limit( LOW_SPEED, 0, motordata -> leg_motor_left.speed );
		  motordata -> leg_motor_right.speed = limit( LOW_SPEED, 0, motordata -> leg_motor_right.speed );
	  }
	  else {
		  speed+=4;
		  motordata -> leg_motor_left.speed  = speed;
      motordata -> leg_motor_right.speed = speed;
	  }
  }
  
   
  //if( !legFlg ) {
	  //motordata -> leg_motor_left.speed  = MAX_SPEED;
    //motordata -> leg_motor_right.speed = MAX_SPEED;
  //}
  //else {
	  //motordata -> leg_motor_left.speed  = LOW_SPEED;
	  //motordata -> leg_motor_right.speed = LOW_SPEED;
  //
}

/**
 *@brief ��i����
 *@param Allmotorsstatus * motordata
 */
void back_legmotor( AllMotorStatus * motordata, char legFlg ){
  motordata -> leg_motor_left.direction  = BACK;
  motordata -> leg_motor_right.direction = BACK;
  
  if( !legFlg ) {
	  if( speed >= MAX_SPEED ) {
		  motordata -> leg_motor_left.speed  = MAX_SPEED;
		  motordata -> leg_motor_right.speed = MAX_SPEED;
		  
		  motordata -> leg_motor_left.speed  = limit( MAX_SPEED, LOW_SPEED, motordata -> leg_motor_left.speed );
		  motordata -> leg_motor_right.speed = limit( MAX_SPEED, LOW_SPEED, motordata -> leg_motor_right.speed );
	  }
	  else {
		  speed+=4;
		  motordata -> leg_motor_left.speed = speed;
		  motordata -> leg_motor_right.speed = speed;
	  }
  }
  else {
	  if( speed >= LOW_SPEED ) {
	    motordata -> leg_motor_left.speed  = LOW_SPEED;
	    motordata -> leg_motor_right.speed = LOW_SPEED;
		
		  motordata -> leg_motor_left.speed  = limit( LOW_SPEED, 0, motordata -> leg_motor_left.speed );
		  motordata -> leg_motor_right.speed = limit( LOW_SPEED, 0, motordata -> leg_motor_right.speed );
	  }
	  else {
		  speed+=4;
		  motordata -> leg_motor_left.speed  = speed;
		  motordata -> leg_motor_right.speed = speed;
	  }
  }
  
  //// �������[�h
  //if( !legFlg ) {
    //motordata -> leg_motor_left.speed  = MAX_SPEED;
    //motordata -> leg_motor_right.speed = MAX_SPEED;
  //}
  //// �ᑬ���[�h
  //else {
    //motordata -> leg_motor_left.speed  = LOW_SPEED;
    //motordata -> leg_motor_right.speed = LOW_SPEED;
  //}
}

/**
 *@brief �E���񓮍�
 *@param Allmotorsstatus * motordata
 */
void turn_right_legmotor( AllMotorStatus * motordata, char legFlg ){
  motordata -> leg_motor_left.direction  = BACK;
  motordata -> leg_motor_right.direction = FORWARD;
  
  if( !legFlg ) {
	  if( speed >= TURN_SPEED ) {
		  motordata -> leg_motor_left.speed  = TURN_SPEED;
		  motordata -> leg_motor_right.speed = TURN_SPEED;
		  
		  motordata -> leg_motor_left.speed  = limit( TURN_SPEED, LOW_TURN_SPEED, motordata -> leg_motor_left.speed );
		  motordata -> leg_motor_right.speed = limit( TURN_SPEED, LOW_TURN_SPEED, motordata -> leg_motor_right.speed );
	  }
	  else {
		  speed+=4;
		  motordata -> leg_motor_left.speed = speed;
		  motordata -> leg_motor_right.speed = speed;
	  }
  }
  else {
	  if( speed >= LOW_SPEED ) {
	    motordata -> leg_motor_left.speed  = LOW_TURN_SPEED;
	    motordata -> leg_motor_right.speed = LOW_TURN_SPEED;
			
		  motordata -> leg_motor_left.speed  = limit( LOW_TURN_SPEED, 0, motordata -> leg_motor_left.speed );
		  motordata -> leg_motor_right.speed = limit( LOW_TURN_SPEED, 0, motordata -> leg_motor_right.speed );
	  }
	  else {
		  speed+=4;
		  motordata -> leg_motor_left.speed  = speed;
		  motordata -> leg_motor_right.speed = speed;
	  }
  }
  
  //if( !legFlg ) {
    //motordata -> leg_motor_left.speed  = TURN_SPEED;
    //motordata -> leg_motor_right.speed = TURN_SPEED;
  //}
  //else {
	  //motordata -> leg_motor_left.speed  = LOW_TURN_SPEED;
    //motordata -> leg_motor_right.speed = LOW_TURN_SPEED;
  //}
}

/**
 *@brief �����񓮍�
 *@param Allmotorstatus * motordata
 */
void turn_left_legmotor( AllMotorStatus * motordata, char legFlg ){
  motordata -> leg_motor_left.direction  = FORWARD;
  motordata -> leg_motor_right.direction = BACK;
  
  if( !legFlg ) {
	  if( speed >= TURN_SPEED ) {
		  motordata -> leg_motor_left.speed  = TURN_SPEED;
		  motordata -> leg_motor_right.speed = TURN_SPEED;
		  
		  motordata -> leg_motor_left.speed  = limit( TURN_SPEED, LOW_TURN_SPEED, motordata -> leg_motor_left.speed );
		  motordata -> leg_motor_right.speed = limit( TURN_SPEED, LOW_TURN_SPEED, motordata -> leg_motor_right.speed );
	  }
	  else {
		  speed+=4;
		  motordata -> leg_motor_left.speed = speed;
		  motordata -> leg_motor_right.speed = speed;
	  }
  }
  else {
	  if( speed >= LOW_SPEED ) {
	    motordata -> leg_motor_left.speed  = LOW_TURN_SPEED;
	    motordata -> leg_motor_right.speed = LOW_TURN_SPEED;
		
		  motordata -> leg_motor_left.speed  = limit( LOW_TURN_SPEED, 0, motordata -> leg_motor_left.speed );
		  motordata -> leg_motor_right.speed = limit( LOW_TURN_SPEED, 0, motordata -> leg_motor_right.speed );
	  }
	  else {
		  speed+=4;
		  motordata -> leg_motor_left.speed  = speed;
		  motordata -> leg_motor_right.speed = speed;
	  }
  }

  //if( !legFlg ) {
    //motordata -> leg_motor_left.speed  = TURN_SPEED;
    //motordata -> leg_motor_right.speed = TURN_SPEED;
  //}
  //else {
	  //motordata -> leg_motor_left.speed  = LOW_TURN_SPEED;
    //motordata -> leg_motor_right.speed = LOW_TURN_SPEED;
  //}
}

/**
 *@brief ��~����
 *@param Allmotorstatus * motordata
 */
void stop_legmotor( AllMotorStatus * motordata ){
	speed = 0;
  motordata -> leg_motor_left.speed  = STOP_SPEED;
  motordata -> leg_motor_right.speed = STOP_SPEED;
}

/**
 *@brief ���~�b�g�֐�
 *@param upper:��� lower;���� target:���䂵�����ϐ�
 *@return ���ʂ����l
 */
uint8_t limit( uint8_t upper, uint8_t lower, uint8_t target ) {
 if(      upper <= target ) return upper;
 else if( lower >= target ) return lower;
 else                       return target;
}
