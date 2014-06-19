/*
 * ADC.h
 *
 * Created: 2013/02/27 22:23:47
 *  Author: Katsuya
 */ 
#ifndef ADC_H_
#define ADC_H_

#define ADPC0  0b01000000
#define ADPC1  0b01000001
#define ADPC2  0b01000010
#define ADPC3  0b01000011
#define ADPC4  0b01000100
#define ADPC5  0b01000101
#define ADPCT  0b01001000  // 温度
#define ADPC11 0b01001110  // 内部電源1.1V

/**
 * AD変換を行うための初期化関数
 * 最初にこの関数を宣言する
 *@param 変換したいピンを指定する。1で変換したいピン0はなし。例：0x04
 */
void initADC(uint8_t ADPIN);

/**
 * AD変換を行う関数
 * initADCで渡したピンと同じ物を渡すこと
 *@param 変換したいピン（defineで宣言されている中から選択して渡すこと）
 *@return 変換結果
 */
int startADC(uint8_t ADPIN);

#endif /* ADC_H_ */