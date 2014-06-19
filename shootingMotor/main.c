/*
 * shootingMotor.c
 *
 * Created: 2013/01/12 0:15:15
 *  Author: katsuya
 */ 
#include <avr/io.h>
#include "I2CSlave.h"
#include "MotorDriver.h"
#include "grip.h"

/*--- �X���[�u�̃A�h���X ---*/
static const char SLAVE_ADDRESS = 0x05;

/*--- I2C�ʐM�̂��߂̊֐� ---*/
void initHandler(uint8_t dat);
void recievehandler(uint8_t dat);
uint8_t sendHandler(void);
void stopHandler(void);

/*--- �ϐ���` ---*/
MotorSignal signal[2];
uint8_t recieveFlg = 0;

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;
	
	//I2C�X���[�u�̏�����
	I2CSlave_init(SLAVE_ADDRESS, INTERRUPT_OFF);
	I2CSlave_setInitEvent(*initHandler);
	I2CSlave_setReceiveEvent(*recievehandler);
	I2CSlave_setSendEvent(*sendHandler);
	I2CSlave_setStopEvent(*stopHandler);
	
	//���[�^�[�h���C�o��PWM������
	MotorDriver_init0();
	MotorDriver_init1();
	
	while(1){
		PORTD |= 0x10;
		I2CSlave_com();
		//���[�^�[�̑��x����
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