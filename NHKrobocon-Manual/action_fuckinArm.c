/*
 * action_fuckinArm.c
 *
 * Created: 2013/02/22 16:13:31
 *  Author: Katsuya
 */ 
#include <avr/io.h>
#include "motor_structure.h"
#include "connect.h"
#include "action_fuckinArm.h"

/************************************************************************/
/* あれだよ、寄せてッッッッッ！！！！上げるッッッッッ！！！！以上       */
/************************************************************************/

void fuckinArm_catch( AllMotorStatus * motordata ) {
  motordata -> fuckinArm_motor_catch.direction = FORWARD;
	motordata -> fuckinArm_motor_catch.speed = 18;
}

void fuckinArm_release( AllMotorStatus * motordata ) {
	motordata -> fuckinArm_motor_catch.direction = BACK;
	motordata -> fuckinArm_motor_catch.speed = 50;
}

void fuckinArm_up( AllMotorStatus  * motordata ) {
	motordata -> fuckinArm_motor_lift.direction = FORWARD;
	motordata -> fuckinArm_motor_lift.speed = 90;
}

void fuckinArm_down( AllMotorStatus * motordata ) {
	motordata -> fuckinArm_motor_lift.direction = BACK;
	motordata -> fuckinArm_motor_lift.speed = 30;
}

void fuckinArm_stop( AllMotorStatus * motordata, char fuckinFlg ) {
	motordata -> fuckinArm_motor_catch.speed = 0;
	
  //if( fuckinFlg == 0 )
	  //motordata -> fuckinArm_motor_lift.byte = FUCKIN_ACT0;
	//else if( fuckinFlg == 1 )
		//motordata -> fuckinArm_motor_lift.byte = FUCKIN_ACT1;
	
	motordata -> fuckinArm_motor_lift.speed = 0;
}