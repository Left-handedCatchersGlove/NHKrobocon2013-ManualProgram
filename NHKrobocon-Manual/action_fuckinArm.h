/*
 * action_fuckinArm.h
 *
 * Created: 2013/01/08 午後 12:44:17
 *  Author: GuestUser
 */ 


#ifndef ACTION_FUCKINARM_H_
#define ACTION_FUCKINARM_H_

// 掴む動作
void fuckinArm_catch( AllMotorStatus * motordata );
// 離す動作
void fuckinArm_release( AllMotorStatus * motordata );

void fuckinArm_up( AllMotorStatus * motordata );

void fuckinArm_down( AllMotorStatus * motordata );
// 動作しない
void fuckinArm_stop( AllMotorStatus * motordata, char fuckinFlg );

#endif /* ACTION_FUCKINARM_H_ */