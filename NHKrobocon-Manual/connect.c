/*
 * connect.c
 *
 * Created: 2013/02/20 14:27:50
 *  Author: Katsuya
 */ 
#include <avr/io.h>
#include "I2CMaster.h"
#include "motor_structure.h"
#include "slave_address.h"
#include "connect.h"

/************************************************************************/
/* 足回りモータ通信                                                     */
/************************************************************************/
void connect_legmotor( AllMotorStatus * motordata ) {
  I2CMaster_start(LEG_MOTOR_ADDRESS, WRITE);
  I2CMaster_write(motordata -> leg_motor_right.byte);
  I2CMaster_write(motordata -> leg_motor_left.byte);
  I2CMaster_stop();
}

/************************************************************************/
/* リーフアーム・サイド（横移動）                                       */
/************************************************************************/
void connect_leafArmSideAndHide_motor( AllMotorStatus * motordata ) {
  I2CMaster_start(LEAFARM_MOTOR_SIDEHIDE_ADDRESS, WRITE);
  I2CMaster_write(motordata -> leafArm_motor_side.byte);
  I2CMaster_write(motordata -> leafArm_motor_hide.byte);
  I2CMaster_stop();
}

/************************************************************************/
/* リーフアーム・ハンド（伸びたり、掴んだりする                         */
/************************************************************************/
void connect_leafArmExtendAndCatch_motor( AllMotorStatus * motordata ) {
  I2CMaster_start(LEAFARM_MOTOR_EXTENDCATCH_ADDRESS, WRITE);
  I2CMaster_write(motordata -> leafArm_motor_extend.byte);
  I2CMaster_write(motordata -> leafArmHand_motor_catch.byte);
  I2CMaster_stop();
}

/************************************************************************/
/* ファッキンアーム                                                     */
/************************************************************************/
void connect_fuckinArmMotor( AllMotorStatus * motordata ) {
  I2CMaster_start(FUCKINARM_MOTOR_ADDRESS, WRITE);
  I2CMaster_write(motordata -> fuckinArm_motor_lift.byte);
  I2CMaster_write(motordata -> fuckinArm_motor_catch.byte);
  I2CMaster_stop();
}

/************************************************************************/
/* 射出機構                                                             */
/************************************************************************/
void connect_shootingMotor( AllMotorStatus * motordata ) {
  I2CMaster_start(SHOOTING_MOTOR_ADDRESS, WRITE);
  I2CMaster_write(motordata -> shooting_motor.byte);
  I2CMaster_write(motordata -> plantLoading_motor.byte);
  I2CMaster_stop();
}

void connectAllSlave( AllMotorStatus * motordata ) {
	connect_legmotor( motordata );
	connect_leafArmSideAndHide_motor( motordata );
	connect_leafArmExtendAndCatch_motor( motordata );
	connect_fuckinArmMotor( motordata );
	connect_shootingMotor( motordata );
}

void connectAllSlaveReset( AllMotorStatus * motordata ) {
	motordata -> leg_motor_left.speed = 0;
	motordata -> leg_motor_right.speed = 0;
	
	motordata -> leafArm_motor_hide.speed = 0;
	motordata -> leafArm_motor_side.speed = 0;
	
	motordata -> leafArmHand_motor_catch.speed = 0;
	motordata -> leafArm_motor_extend.speed = 0;
	
	motordata -> fuckinArm_motor_catch.speed = 0;
	motordata -> fuckinArm_motor_lift.speed = 0;
	
	motordata -> shooting_motor.speed = 0;
	motordata -> plantLoading_motor.speed = 0;
	
	connectAllSlave( motordata );
}