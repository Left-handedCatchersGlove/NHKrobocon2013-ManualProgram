/*
 * leafArm_action.h
 *
 * Created: 2012/12/26 午前 11:57:55
 *  Author: katsuya
 */ 

#ifndef LEAFARM_ACTION_H_
#define LEAFARM_ACTION_H_

/**
 *  アームが（左右）動かない
 * @param Allmotorstatus * motordata
 */
void leafArmSide_stop( AllMotorStatus * motordata, char leafFlg );

void leafArmSide_prototype_open( AllMotorStatus * motordata );
void leafArmSide_prototype_close( AllMotorStatus * motordata );

/**
 *  アームが上に動く
 * @param Allmotorstatus * motordata
 */
void leafArmHide_up( AllMotorStatus * motordata );

/**
 *  アームが下に動く
 * @param Allmotorstatus * motordata
 */
void leafArmHide_down( AllMotorStatus * motordata );

/**
 *  アームが（上下）に動かない
 * @param Allmotorstatus * motordata
 */
void leafArmHide_stop( AllMotorStatus * motordata );
/**
 *  アームが伸びる
 * @param Allmotorstatus * motordata
 */
void leafArmExtend_extend( AllMotorStatus * motordata );

/**
 *  アームが縮む
 * @param Allmotorstatus * motordata
 */
void leafArmExtend_shrink( AllMotorStatus * motordata );

/**
 *  アームが（伸縮）しない
 * @param Allmotorstatus * motordata
 */
void leafArmExtend_stop( AllMotorStatus * motordata );

/**
 *  ハンドが掴む
 * @param Allmotorstatus * motordata
 */
void leafArmHandCatch_catch( AllMotorStatus * motordata);

/**
 *  ハンドが放す
 * @param Allmotorstatus * motordata
 */
void leafArmHandCatch_release( AllMotorStatus * motordata);

/**
 *  ハンドの動作停止
 * @param Allmotorstatus * motordata
 */
void leafArmHandCatch_stop( AllMotorStatus * motordata );

#endif /* LEAFARM_ACTION_H_ */