/*
 * Manual_LegMotor.c
 *
 * Created: 2012/03/13 17:03:12
 *  Author: Katsuya
 */

#include <avr/io.h>
#include "I2CSlave.h"
#include "grip.h"

//Slaveのアドレス
static const int SLAVE_ADDRESS = 0x02;

//#define WAIT_RELAY 12
#define WAIT_RELAY 7
#define CHANGE 25

//Motorに関しての変数
MotorSignal signals[2] = {0, 0};
uint8_t recieveFlag = 0;
uint8_t sendFlag = 0;

//I2Cについての関数プロトタイプ宣言
void initHandler(uint8_t dat);
void recieveHandler(uint8_t dat);
uint8_t sendHandler(void);
void stopHandler(void);

//初期化関数のプロトタイプ宣言
void timer_pwm_init(void);
void io_init(void);
void timer0_init(void);
void setTergetSpeed(int a, int b);
void startMotorFunc(void);

// Math func 
int check_sign(int i);
int absolute(int i);

// Motor off 
void set_off_motor_a(void);
void set_off_motor_b(void);

//モーターのスピードに関しての関数
void setSpeedMotorA(int spd);
void setSpeedMotorB(int spd);

//モーターのチャタリング
void wait_motor_a_chattering(void);
void wait_motor_b_chattering(void);

// Motor sub func
void chenge_direction_a(void);
void chenge_direction_b(void);
void chenge_direction_a(void);
void chenge_direction_b(void);

//モーターのメイン処理
void set_motor_a(void);
void set_motor_b(void);

//グローバル変数の初期化
int terget_spd_a = 0, terget_spd_b = 0;
void (*motor_a_func_p)(void) = set_motor_a;
void (*motor_b_func_p)(void) = set_motor_b;


//スピード取得
int chengeSignalToSpeed(MotorSignal signal){
	if(signal.direction == FORWARD){
		return signal.speed;
	}	
    else if(signal.direction == BACKWARD){
		return signal.speed * -1;
	}	
}

//タイマー割り込み関数
ISR(TIMER0_OVF_vect){
	startMotorFunc();
}

//************************Main関数****************************
int main(void)
{
	//初期化
	timer_pwm_init();
	io_init();
	timer0_init();
	
	//I2CSlaveの初期化
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
		setTergetSpeed(chengeSignalToSpeed(signals[0]),chengeSignalToSpeed(signals[1]));
	}
}

//*************************************************************


//***********************I2Cに関しての関数*********************
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

//**************************************************************


//************************初期化関数****************************
void timer_pwm_init(void){
	OCR1A = 0xFF;
	OCR1B = 0xFF;
	TCCR1A = 0xF1;
	TCCR1B = 0x0A;
}

void io_init(void){
	PORTB = 0x00;
	DDRB = 0x1E;
}

void timer0_init(void){
	TCCR0B = 0x03;
	TIMSK0 = 0x01;
}
//**************************************************************


//************************ Math func ***************************
int check_sign(int i){
	if(i >= 0){
		return 1;   // + の符号の時  1 を返す
	}		
	else{
		return -1;  // - の符号の時 -1 を返す
	}		
}

int absolute(int i){
	/*引数の絶対値を返す*/
	if(i >= 0){
		return i;
	}		
	if(i < 0){
		return -i;
	}		
}

//*************************************************************


//*********************** Motor off ***************************

//Motor A off
void set_off_motor_a(void){
	OCR1A = 255;
}

//Motor B off
void set_off_motor_b(void){
	OCR1B = 255;
}

//*************************************************************


//*************モーターのスピードに関しての関数****************
void setSpeedMotorA(int spd){
	int speed;
	speed = absolute(spd);
	if(speed > 255)
    speed = 255;
	OCR1A = 255 - speed;
}

void setSpeedMotorB(int spd){
	int speed;
	speed = absolute(spd);
    if(speed > 255)
    speed = 255;
    OCR1B = 255 - speed;
}

//************************************************************


//*******************モーターのチャタリング*******************
void wait_motor_a_chattering(void){
  static int i = 0;
  
  if(i < WAIT_RELAY){
		i += 1;
  }
  else{
		i = 0;
		motor_a_func_p = set_motor_a;
  }
}

void wait_motor_b_chattering(void){
  static int i = 0;
  
  if(i < WAIT_RELAY){
		i += 1;
  }
  else{
        i = 0;
        motor_b_func_p = set_motor_b;
  }
}

//*************************************************************


//******************** Motor sub func *************************
void chenge_direction_a(void){
	PORTB ^= 0x08;
}

void chenge_direction_b(void){
	PORTB ^= 0x10;
}

//*************************************************************

int limit(int val, int min, int max){
	if(val < min)
		return min;
	else if(val > max)
		return max;
	else
		return val;
}


//********************モーターのメイン処理*********************
void set_motor_a(void){
	static int nowspeed = 0;
	static int nextspeed = 0;
  
	if(nextspeed < terget_spd_a)
		nextspeed = limit(nowspeed + CHANGE, -255 / 2, terget_spd_a);
	else if(nextspeed > terget_spd_a)
		nextspeed = limit(nowspeed - CHANGE, terget_spd_a, 255 / 2);
  
	if(check_sign(nowspeed) != check_sign(nextspeed)){
		set_off_motor_a();
		chenge_direction_a();
		nowspeed = nextspeed;
		motor_a_func_p = wait_motor_a_chattering;
	}
	else{
		nowspeed = nextspeed;
		setSpeedMotorA(nowspeed * 2);
	}
}	

void set_motor_b(void){
	static int nowspeed = 0;
	static int nextspeed = 0;
	
	if(nextspeed < terget_spd_b)
		nextspeed = limit(nowspeed + CHANGE, -255 / 2, terget_spd_b);
	else if(nextspeed > terget_spd_b)
		nextspeed = limit(nowspeed - CHANGE, terget_spd_b, 255 / 2);
  
  if(check_sign(nowspeed) != check_sign(nextspeed)){
	  set_off_motor_b();
	  chenge_direction_b();
	  nowspeed = nextspeed;
    motor_b_func_p = wait_motor_b_chattering;
  }
  else{
    nowspeed = nextspeed;
	  setSpeedMotorB(nowspeed * 2);
  }
}	

void setTergetSpeed(int a, int b){
	terget_spd_a = a;
	terget_spd_b = b;
}

void startMotorFunc(void){
  motor_a_func_p();
  motor_b_func_p();
}

//*********************************************************