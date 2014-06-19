/*
 * action_shooting.h
 *
 * Created: 2013/01/12 0:18:12
 *  Author: KatsuyaS
 */ 
#ifndef ACTION_SHOOTING_H_
#define ACTION_SHOOTING_H_

void shoot( AllMotorStatus * motordata );

void shoot_stop( AllMotorStatus * motordata );

void plantLoading( AllMotorStatus * motordata );

void plantLoading_stop( AllMotorStatus * motordata );

#endif /* ACTION_SHOOTING_H_ */