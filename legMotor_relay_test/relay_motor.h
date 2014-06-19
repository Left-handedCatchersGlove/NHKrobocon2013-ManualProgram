/*
 * relay_motor.h
 *
 * Created: 2013/03/24 23:16:04
 *  Author: Chelly
 */ 

#ifndef RELAY_MOTOR_H_
#define RELAY_MOTOR_H_

static const CHANGE = 25;
static const WAIT_RELAY = 5;

/**
 *@brief PWMに関しての初期化関数
 */
void timer_pwm_init(void);

/**
 *@brief 入出力に関しての初期化関数
 */
void io_init(void);

/**
 *@brief タイマーに関しての初期化関数
 */
void timer0_init(void);

/**
 *@brief タイマー割り込みによって呼び出される関数モータの動きを決定するための関数ポインタを動かす
 */
void startMotorFunc(void);

/**
 *@brief 引数の絶対値を返す関数
 *@param targe：取りたい値
 *@return 絶対値
 */
int absolute(int target);

/**
 *@brief 絶対値をとる関数
 *@param i:絶対値をとる値
 *@return 絶対値
 */
int check_sign( int * i );

/**
 *@brief Aモータのスピードに関しての関数
 *@param speed：スピードを受け取る
 */
void setSpeedMotorA( int a_speed );

/**
 *@brief Aモータをオフにする
 */
void set_off_motor_a(void);

/**
 *@brief Aモータの回転方向を変える
 */
void chenge_direction_a(void);

/**
 *@brief Aモータのチャタリング防止
 */
void wait_motor_a_chatterring(void);

/**
 *@brief Aモータのメイン関数
 */
void set_motor_a(void);

/**
 *@brief Bモータのスピードに関しての関数
 *@param speed：スピードを受け取る
 */
void setSpeedMotorB(int b_speed);

/**
 *@brief Bモータをオフにする
 */
void set_off_motor_b(void);

/**
 *@brief Bモータの回転方向を変える
 */
void chenge_direction_b(void);

/**
 *@brief Bモータのチャタリング防止
 */
void wait_motor_b_chatterring(void);

/**
 *@brief Bモータのメイン関数
 */
void set_motor_b(void);

void setTargetSpeed( int a, int b );

#endif /* RELAY_MOTOR_H_ */