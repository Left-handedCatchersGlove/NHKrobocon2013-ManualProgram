/*
 * leafArmMotor_SideAndHide.c
 *
 * Created: 2012/12/28 午後 04:01:36
 *  Author: GuestUser
 */ 

#include <avr/io.h>
#include "I2CSlave.h"
#include "MotorDriver.h"
#include "grip.h"
#include "ADC.h"

/*--- スレーブのアドレス ---*/
static const char SLAVE_ADDRESS = 0x81;

/*--- I2C通信のための関数 ---*/
void initHandler(uint8_t dat);
void recievehandler(uint8_t dat);
uint8_t sendHandler(void);
void stopHandler(void);

/*--- 変数定義 ---*/
MotorSignal signal[2];
uint8_t recieveFlg = 0;

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;
	
	//I2Cスレーブの初期化
	I2CSlave_init(SLAVE_ADDRESS, INTERRUPT_OFF);
	I2CSlave_setInitEvent(*initHandler);
	I2CSlave_setReceiveEvent(*recievehandler);
	I2CSlave_setSendEvent(*sendHandler);
	I2CSlave_setStopEvent(*stopHandler);
	
	initADC( ADPC3 );
	
	//モータードライバのPWM初期化
	MotorDriver_init0();
	MotorDriver_init1();
	
	while(1){
		PORTD |= 0x10;
		I2CSlave_com();
		
		//モーターの速度決定
		MotorDriver_run0(signal[0]);
		MotorDriver_run1(signal[1]);
	}
}

void initHandler(uint8_t dat){}

void recievehandler(uint8_t dat){
	signal[recieveFlg].key = dat;
	++recieveFlg;
}

uint8_t sendHandler(void){}

void stopHandler(void){
	recieveFlg = 0;
}