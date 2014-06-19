/*
 * leg_action.h
 *
 * Created: 2012/08/19 23:11:17
 *  Author: katsuya
 */

#ifndef LEGMOTOR_ACTION_H_
#define LEGMOTOR_ACTION_H_

/**
 *@brief 前進動作
 *@param AllMotorStatus * motordata
 */
void leg_motor_Prototype( AllMotorStatus * motordata, char legFlg );

/**
 *@brief 後進動作
 *@param Allmotorsstatus * motordata
 */
void back_legmotor( AllMotorStatus * motordata, char legFlg );

/**
 *@brief 右旋回動作
 *@param AllMotorStatus * motordata
 */
void turn_right_legmotor( AllMotorStatus * motordata, char legFlg );

/**
 *@brief 左旋回動作
 *@param AllMotorStatus * motordata
 */
void turn_left_legmotor( AllMotorStatus * motordata, char legFlg );

/**
 *@brief 停止動作
 *@param AllMotorStatus * motordata
 */
void stop_legmotor( AllMotorStatus * motordata );

/**
 *@brief リミット関数
 *@param upper:上限 lower:下限 target:目標の値
 *@return int型:上限下限範囲の値
 */
uint8_t limit( uint8_t upper, uint8_t lower, uint8_t target );

#endif /* LEGMOTOR_ACTION_H_ */
