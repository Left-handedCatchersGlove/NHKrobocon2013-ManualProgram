/*
 * action_shooting.h
 *
 * Created: 2013/01/12 0:18:12
 *  Author: Katsuya
 */ 
 
#include <avr/io.h>
#include "motor_structure.h"
#include "connect.h"
#include "action_shooting.h"

void shoot( AllMotorStatus * motordata ) {
  motordata -> shooting_motor.direction = FORWARD;
  motordata -> shooting_motor.speed = 30;
}

void shoot_stop( AllMotorStatus * motordata ) {
  motordata -> shooting_motor.speed = STOP_SPEED;
}

void plantLoading( AllMotorStatus * motordata ) {
  motordata -> plantLoading_motor.direction = FORWARD;
  motordata -> plantLoading_motor.speed = 30;
}

void plantLoading_stop( AllMotorStatus * motordata ){
  motordata -> plantLoading_motor.speed = STOP_SPEED;
}