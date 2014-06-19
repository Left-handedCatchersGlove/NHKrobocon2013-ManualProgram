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
 *@brief PWM�Ɋւ��Ă̏������֐�
 */
void timer_pwm_init(void);

/**
 *@brief ���o�͂Ɋւ��Ă̏������֐�
 */
void io_init(void);

/**
 *@brief �^�C�}�[�Ɋւ��Ă̏������֐�
 */
void timer0_init(void);

/**
 *@brief �^�C�}�[���荞�݂ɂ���ČĂяo�����֐����[�^�̓��������肷�邽�߂̊֐��|�C���^�𓮂���
 */
void startMotorFunc(void);

/**
 *@brief �����̐�Βl��Ԃ��֐�
 *@param targe�F��肽���l
 *@return ��Βl
 */
int absolute(int target);

/**
 *@brief ��Βl���Ƃ�֐�
 *@param i:��Βl���Ƃ�l
 *@return ��Βl
 */
int check_sign( int * i );

/**
 *@brief A���[�^�̃X�s�[�h�Ɋւ��Ă̊֐�
 *@param speed�F�X�s�[�h���󂯎��
 */
void setSpeedMotorA( int a_speed );

/**
 *@brief A���[�^���I�t�ɂ���
 */
void set_off_motor_a(void);

/**
 *@brief A���[�^�̉�]������ς���
 */
void chenge_direction_a(void);

/**
 *@brief A���[�^�̃`���^�����O�h�~
 */
void wait_motor_a_chatterring(void);

/**
 *@brief A���[�^�̃��C���֐�
 */
void set_motor_a(void);

/**
 *@brief B���[�^�̃X�s�[�h�Ɋւ��Ă̊֐�
 *@param speed�F�X�s�[�h���󂯎��
 */
void setSpeedMotorB(int b_speed);

/**
 *@brief B���[�^���I�t�ɂ���
 */
void set_off_motor_b(void);

/**
 *@brief B���[�^�̉�]������ς���
 */
void chenge_direction_b(void);

/**
 *@brief B���[�^�̃`���^�����O�h�~
 */
void wait_motor_b_chatterring(void);

/**
 *@brief B���[�^�̃��C���֐�
 */
void set_motor_b(void);

void setTargetSpeed( int a, int b );

#endif /* RELAY_MOTOR_H_ */