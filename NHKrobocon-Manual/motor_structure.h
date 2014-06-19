/*
 * motor_structure.h
 *
 * Created: 2012/08/09 17:00:28
 *  Author: Katsuya
 */

#ifndef MOTOR_STRUCTURE_H_
#define MOTOR_STRUCTURE_H_

/*** モータの共用体 ***/
typedef union MotorStatus {
  uint8_t byte: 8;
  struct {
    unsigned char direction: 1;
    unsigned char speed: 7;
  };
} MotorStatus;

/*** 各モータの構造体 ***/
typedef struct AllMotorStatus{
  MotorStatus leg_motor_left;
  MotorStatus leg_motor_right;
  
  MotorStatus leafArm_motor_side;
  MotorStatus leafArm_motor_hide;
  MotorStatus leafArm_motor_extend;
  MotorStatus leafArmHand_motor_catch;
  
  MotorStatus fuckinArm_motor_catch;
  MotorStatus fuckinArm_motor_lift;
  
  MotorStatus shooting_motor;
  MotorStatus plantLoading_motor;
} AllMotorStatus;

/*===== モータパラメータ =====*/
static const uint8_t FORWARD = 0;
static const uint8_t BACK = 1;
static const uint8_t MAX_SPEED  = 255 >> 1;
static const uint8_t LOW_SPEED  = 60;
static const uint8_t TURN_SPEED = 60;
static const uint8_t LOW_TURN_SPEED = 40;
static const uint8_t STOP_SPEED = 0;

/*===== スレーブに指定するためのパラメータ =====*/
// リーフアームの開閉のための角度指定
static const uint8_t LEAF_START = 0;
static const uint8_t LEAF_OPEN  = 40;
static const uint8_t LEAF_CLOSE = 100;

// ファッキンアームの位置指定
static const uint8_t FUCKIN_ACT0 = 0b0000001;
static const uint8_t FUCKIN_ACT1 = 0b0000010;
static const uint8_t FUCKIN_ACT2 = 0b0000100;
static const uint8_t FUCKIN_ACT3 = 0b0001000;
static const uint8_t FUCKIN_ACT4 = 0b0010000;

#endif /* MOTOR_STRUCTURE_H_ */