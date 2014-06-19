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
*@brief 前進動作(カーブあり)
 *@param Allmotorstatus * motordata
 */
void front_legmotor( AllMotorStatus * motordata, uint8_t rudder, char legFlg ){
  uint8_t speed = 0;
  motordata -> leg_motor_left.direction = FORWARD;
  motordata -> leg_motor_right.direction = FORWARD;
  
  if( legFlg == 0 ) {
    if( 117 < rudder && rudder < 137 ) { // 直進動作
      motordata -> leg_motor_left.speed  = MAX_SPEED;
      motordata -> leg_motor_right.speed = MAX_SPEED;
    }
    else if( rudder <= 117 ) { // 左カーブ動作
      motordata -> leg_motor_right.speed = MAX_SPEED;
      speed = (uint8_t)( (float)( ( ( 107.0 / 117.0 ) * rudder ) + LOW_SPEED ) );
      motordata -> leg_motor_left.speed = speed;
    }
    else if( rudder >= 137 ) { // 右カーブ動作
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
 *@brief 前進関数(カーブなし)
 *@param AllmototStatus * motordata 構造体のポインタ
 */
void leg_motor_Prototype( AllMotorStatus * motordata, char legFlg ) {
  motordata -> leg_motor_left.direction  = FORWARD;
  motordata -> leg_motor_right.direction = FORWARD;
  
  // 高速モード
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
  // 低速モード
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
 *@brief 後進動作
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
  
  //// 高速モード
  //if( !legFlg ) {
    //motordata -> leg_motor_left.speed  = MAX_SPEED;
    //motordata -> leg_motor_right.speed = MAX_SPEED;
  //}
  //// 低速モード
  //else {
    //motordata -> leg_motor_left.speed  = LOW_SPEED;
    //motordata -> leg_motor_right.speed = LOW_SPEED;
  //}
}

/**
 *@brief 右旋回動作
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
 *@brief 左旋回動作
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
 *@brief 停止動作
 *@param Allmotorstatus * motordata
 */
void stop_legmotor( AllMotorStatus * motordata ){
	speed = 0;
  motordata -> leg_motor_left.speed  = STOP_SPEED;
  motordata -> leg_motor_right.speed = STOP_SPEED;
}

/**
 *@brief リミット関数
 *@param upper:上限 lower;下限 target:制御したい変数
 *@return 判別した値
 */
uint8_t limit( uint8_t upper, uint8_t lower, uint8_t target ) {
 if(      upper <= target ) return upper;
 else if( lower >= target ) return lower;
 else                       return target;
}
