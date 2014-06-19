/*
 * main.c
 *
 * Created: 2013/03/05 12:08:48
 *  Author: GuestUser
 */ 

#include <avr/io.h>
#include "hBridge.h"
#include "I2CSlave.h"

void i2c_init_Handler(unsigned char dat);
void i2cRecieveHandler1(uint8_t dat);
void i2c_set_stop_Handler();
uint8_t i2cSendHandler();

static const uint8_t SLAVE_ADDRESS = 0x01;

int flg = 0;

int main(void)
{
	initHbridge();
	I2CSlave_init(SLAVE_ADDRESS, INTERRUPT_OFF);
	I2CSlave_setInitEvent(*i2c_init_Handler);
	I2CSlave_setReceiveEvent(*i2cRecieveHandler1);
  I2CSlave_setSendEvent(*I2CSlave_setSendEvent);
	I2CSlave_setStopEvent(*i2c_set_stop_Handler);
	
	while(1) {
		I2CSlave_com();
	}
}

void i2c_init_Handler(unsigned char dat){}
	
void i2cRecieveHandler1(uint8_t dat){
	if(flg == 0){
    D_motordata.byte = dat;
	  flg++;
	}	  
	else if(flg == 1){
		B_motordata.byte = dat;
		flg=0;
	}	
}

uint8_t i2cSendHandler(){}

void i2c_set_stop_Handler(){
	if ( D_motordata.speed == 0 ) D_pwmControl( 0, 0 );
	else
	{
		if ( D_motordata.direction == 0 ) D_pwmControl( 2, ( ( (char)( D_motordata.speed) ) << 1 ) + 1 );
		else D_pwmControl( 3, ( ( (char)(D_motordata.speed) ) << 1 ) + 1 );
	}
	
	if ( B_motordata.speed == 0 ) B_pwmControl( 0, 0 );
	else
	{
		if ( B_motordata.direction == 0 ) B_pwmControl( 2, ( ( (char)( B_motordata.speed) ) << 1 ) + 1 );
		else B_pwmControl( 3, ( ( (char)(B_motordata.speed) ) << 1 ) + 1 );
	}
	
	flg = 0;
}