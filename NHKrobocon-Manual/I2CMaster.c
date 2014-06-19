/*
 * I2CMaster.c
 *
 * Created: 2012/08/09 16:34:00
 *  Author: Katsuya
 */ 
#include <avr/io.h>
#include "I2CMaster.h"

/**
 * I2Cを初期化します。ここで通信の速度を設定します。通信のクロック数は
 * [ クロック = (CPUクロック周波数) / (16 + 2 * bitRate * prescaler) ]で設定されます。
 * @param bitRate TWIの速度の分周値
 * @param prescaler TWIのビット速度の前置分周値
 */
void I2CMaster_init(uint8_t bitRate, uint8_t prescaler) {
    // プリスケーラは下位2bitのみで設定されます。
    // そのため、上位6bitの値を0にします。
	prescaler &= 0x03;
	TWBR = bitRate;
	TWSR = prescaler;
	TWCR = _BV(TWEN);
}

/**
 * スタートコンディションを発行し、スレーブのアドレスを送信します。
 * (送信の場合でもビットシフトしたスレーブアドレスを渡す必要はありません)
 * @param address 通信するスレーブアドレス
 * @param mode  送信:WRITE(0) or 受信:READ(1)を指定
 */
void I2CMaster_start(unsigned char address, I2CMode mode) {
	// スタートコンディションの発行
    TWCR = I2CMaster_START_CONDITION;
    // スタートコンディションの発行完了待ち
    while(!I2CMaster_isTWINT()) {
    }

	// まず、アドレスを1ビット左にシフトし、
	// 受信の場合は下位1ビットを1にする。
	// 送信の場合は下位1ビットは0にする。
    address <<= 1;
	
	switch(mode) {
		case WRITE:
		    address &= 0b11111110;  // address = 0bxxxxxxx0 に
		    break;
	    case READ:
		    address |= 0b00000001;   // address = 0bxxxxxxx1に
		    break;
	}
	
	// スレーブアドレスの送信
    I2CMaster_write(address);
}

/**
 * ストップコンディションを発行します。
 */
void I2CMaster_stop() {
	// ストップコンディションの発行
	TWCR = I2CMaster_STOP_CONDITION;
}

/**
 * データを送信します。
 * @param dat 送信するデータ
 * @return 1:ACK / 0:NOACK
 */
unsigned char I2CMaster_write(unsigned char dat) {
    // 送信するデータを設定
    TWDR = dat;
    // 送信開始
    TWCR = I2CMaster_CLEAR_TWINT;
    // 送信完了待ち
    while(!I2CMaster_isTWINT()){
    }
	// ACKの受信完了待ち
	// while(!(TWCR & 1<<TWINT)) {} これ不要？ 要確認
	
    // ACK値をチェック
    if(I2CMaster_isACK()) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * データを受信します
 * @param ack
 * @return 受信データ
 */
unsigned char I2CMaster_read(unsigned char ack) { //0で受信するが、１を渡すと終了の合図になる
    if(ack == 0) {
        // ACK応答
        TWCR = (I2CMaster_CLEAR_TWINT | 1<<TWEA);
    } else {
        // NOACK応答
        TWCR = I2CMaster_CLEAR_TWINT;
    }
	
    // データの受信完了待ち
    while(!(TWCR & _BV(TWINT))){
    }
    return TWDR;
}

/**
 * TWCRレジスタのTWINTの値を返します。
 * @return TWINTが1なら1, 0なら0
 */
unsigned char I2CMaster_isTWINT() {
    if(TWCR & _BV(TWINT)) {
        return 1;
    } else {
        return 0;
    }
}

unsigned char I2CMaster_isACK() {
	if((TWSR & 0xF8) == I2CMaster_TWSR_DAT_ACK) {
	    return 1;
	} else {
		return 0;
	}
	/*
    switch(TWSR & 0xF8) {
        case I2CMaster_TWSR_SLA_W_ACK:
        case I2CMaster_TWSR_SLA_R_ACK:
        case I2CMaster_TWSR_DAT_ACK:// ACK
            return 1;
        default:// NOACK
            return 0;
    } */
}