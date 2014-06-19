/*
 * Manual_LegMotor.c
 *
 * Created: 2012/03/13 17:03:12
 *  Author: Katsuya
 */

#include <avr/io.h>
#include "grip.h"
#include "I2CSlave.h"
#include "relay_motor.h"

//Slaveのアドレス
static const int SLAVE_ADDRESS = 0x01;

// Motorに関しての変数
MotorSignal signals[2] = {0, 0};
uint8_t recieveFlag = 0;
uint8_t sendFlag = 0;

//I2Cについての関数プロトタイプ宣言
void initHandler(uint8_t dat);
void recieveHandler(uint8_t dat);
uint8_t sendHandler(void);
void stopHandler(void);

//タイマー割り込み関数
ISR(TIMER0_OVF_vect){
	startMotorFunc();
}

//************************Main関数****************************
int main(void)
{
	// 初期化
	timer_pwm_init();
	io_init();
	timer0_init();
	
	// I2CSlaveの初期化
	I2CSlave_init(SLAVE_ADDRESS,INTERRUPT_OFF);
	I2CSlave_setInitEvent(*initHandler);
	I2CSlave_setSendEvent(*sendHandler);
	I2CSlave_setReceiveEvent(*recieveHandler);
	I2CSlave_setStopEvent(*stopHandler);
	
	//割り込み許可
	sei();
	
	while(1){
		//I2C通信
		I2CSlave_com();
		setTargetSpeed(chengeSignalToSpeed(signals[0]),chengeSignalToSpeed(signals[1]));
	}
}

//スピード取得
int chengeSignalToSpeed(MotorSignal signal){
	if(signal.direction == FORWARD){
		return signal.speed;
	}	
    else if(signal.direction == BACKWARD){
		return signal.speed * -1;
	}	
}

void initHandler(uint8_t dat){}
	
void recieveHandler(uint8_t dat){
	signals[recieveFlag].key = dat;
	++recieveFlag;
}

uint8_t sendHandler(){
	MotorSignal ms = signals[sendFlag];
	++sendFlag;
	return ms.key;
}

void stopHandler(){
	recieveFlag = 0;
	sendFlag = 0;
}

int limit(int val, int min, int max){
	if(val < min)
		return min;
	else if(val > max)
		return max;
	else
		return val;
}

//*********************************************************