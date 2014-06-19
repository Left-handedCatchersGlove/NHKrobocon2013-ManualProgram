/*
 * action_leafArm.c
 *
 * Created: 2013/02/22 16:58:25
 *  Author: kubrick
 */ 
#include <avr/io.h>
#include "motor_structure.h"
#include "connect.h"
#include "action_leafArm.h"

void leafArmSide_prototype_open( AllMotorStatus * motordata ) {
	motordata -> leafArm_motor_side.direction = FORWARD;
	motordata -> leafArm_motor_side.speed = 35;
}
	
void leafArmSide_prototype_close( AllMotorStatus * motordata ) {
	motordata -> leafArm_motor_side.direction = BACK;
	motordata -> leafArm_motor_side.speed = 35;
}

/**
 *@brief �A�[�����i���E�j�����Ȃ��Ƃ��������⓮���񂾂Ȃ����ꂪ
 *@param Allmotorstatus * motordata
 */
void leafArmSide_stop( AllMotorStatus * motordata, char leafFlg ) {
	motordata -> leafArm_motor_side.speed = 0;
	
  //if( leafFlg == 0 )
	  //motordata -> leafArm_motor_side.byte = LEAF_CLOSE;
  //else if( leafFlg == 1 )
	  //motordata -> leafArm_motor_side.byte = LEAF_OPEN;
  //else if( leafFlg == 2 )
	  //motordata -> leafArm_motor_side.byte = LEAF_START;
}


/**
 *  �A�[������ɓ���
 * @param Allmotorstatus * motordata
 */
void leafArmHide_up( AllMotorStatus * motordata ) {
	motordata -> leafArm_motor_hide.direction = BACK;
	motordata -> leafArm_motor_hide.speed = MAX_SPEED;
}

/**
 *  �A�[�������ɓ���
 * @param Allmotorstatus * motordata
 */
void leafArmHide_down( AllMotorStatus * motordata ) {
	motordata -> leafArm_motor_hide.direction = FORWARD;
	motordata -> leafArm_motor_hide.speed = MAX_SPEED;
}

/**
 *  �A�[�����i�㉺�j�ɓ����Ȃ�
 * @param Allmotorstatus * motordata
 */
void leafArmHide_stop( AllMotorStatus * motordata ) {
	motordata -> leafArm_motor_hide.speed = 0;
}

/**
 *  �A�[�����L�т�
 * @param Allmotorstatus * motordata
 */
void leafArmExtend_extend( AllMotorStatus * motordata ) {
	motordata -> leafArm_motor_extend.direction = FORWARD;
	motordata -> leafArm_motor_extend.speed = MAX_SPEED;
}

/**
 *  �A�[�����k��
 * @param Allmotorstatus * motordata
 */
void leafArmExtend_shrink( AllMotorStatus * motordata ) {
	motordata -> leafArm_motor_extend.direction = BACK;
	motordata -> leafArm_motor_extend.speed = MAX_SPEED;
}

/**
 *  �A�[�����i�L�k�j���Ȃ�
 * @param Allmotorstatus * motordata
 */
void leafArmExtend_stop( AllMotorStatus * motordata ) {
	motordata -> leafArm_motor_extend.speed = 0;
}

/**
 *  �n���h���͂�
 * @param Allmotorstatus * motordata
 */
void leafArmHandCatch_catch( AllMotorStatus * motordata) {
	motordata -> leafArmHand_motor_catch.direction = BACK;
	motordata -> leafArmHand_motor_catch.speed = MAX_SPEED;
}

/**
 *  �n���h������
 * @param Allmotorstatus * motordata
 */
void leafArmHandCatch_release( AllMotorStatus * motordata) {
	motordata -> leafArmHand_motor_catch.direction = FORWARD;
	motordata -> leafArmHand_motor_catch.speed = MAX_SPEED;
}

void leafArmHandCatch_stop( AllMotorStatus * motordata ) {
	motordata -> leafArmHand_motor_catch.speed = 0;
}