/*
 * hBridge.h
 *
 * Created: 2013/02/25 22:01:20
 *  Author: Katsuya
 */ 

#ifndef HBRIDGE_H_
#define HBRIDGE_H_

/*=== PWM設定 ===*/
#define ADVANCE 0x83
#define RETREAT 0x23
#define FREE    0x03
#define MYSTOP    0xA3

/*=== Dポート設定 ===*/
#define D_FREE    0x90
#define D_STOP    0x90
#define D_ADVANCE 0x80
#define D_RETREAT 0x10

/*=== Bポート設定 ===*/
#define B_FREE    0x14
#define B_STOP    0x14
#define B_ADVANCE 0x04
#define B_RETREAT  0x10

typedef union MotorStatus {
	uint8_t byte: 8;
	struct {
		unsigned char direction: 1;
		unsigned char speed: 7;
	};
} MotorStatus;

MotorStatus D_motordata, B_motordata;

// 回転方向記録のための変数
static uint8_t pre_Dinput = 0;
static uint8_t pre_Binput = 0;

/**
 *  初期化関数
 * @param  none
 */
void initHbridge(void);

/**
 *  DポートのPWM制御
 * @param 回転方向成分:direction, スピード成分:speed
 */
void D_pwmControl(uint8_t direction, uint8_t speed);

/**
 *  Dポートの回転方向制御
 * @param 回転方向成分:directionのポインタ
 */
void D_portDirectionChange(uint8_t * direction);

/**
 *  DポートのPWMを操作
 * @param 回転方向成分:direction, スピード成分:speed
 */
void B_pwmControl(uint8_t direction, uint8_t speed);

/**
 *  Bポートの回転方向制御
 * @param 回転方向成分:directionのポインタ
 */
void B_portDirectionChange(uint8_t * direction);

#endif /* HBRIDGE_H_ */