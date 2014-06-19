/*
 * I2CMaster.h
 *
 * Created: 2011/12/07 17:18:24
 *  Author: Katsuya
 */


#ifndef I2CMASTER_H_
#define I2CMASTER_H_

#include <avr/io.h>

static const uint8_t I2CMaster_PRESCALER_1 = 0x00;    // TWIプリスケーラ分周値1
static const uint8_t I2CMaster_PRESCALER_4 = 0x01;    // TWIプリスケーラ分周値4
static const uint8_t I2CMaster_PRESCALER_16 = 0x02;   // TWIプリスケーラ分周値16
static const uint8_t I2CMaster_PRESCALER_64 = 0x03;   // TWIプリスケーラ分周値64

// TWSR状態値
static const int I2CMaster_TWSR_SLA_W_ACK = 0x18;
static const int I2CMaster_TWSR_SLA_R_ACK = 0x40;
static const int I2CMaster_TWSR_DAT_ACK = 0x28;

// TWBRレジスタのコンディション
static const uint8_t I2CMaster_START_CONDITION = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
static const uint8_t I2CMaster_STOP_CONDITION = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
static const uint8_t I2CMaster_CLEAR_TWINT = (1<<TWINT) | (1<<TWEN);

typedef enum I2CMode {
    WRITE = 0,
	READ = 1
} I2CMode;

typedef enum Ack {
	ACK = 0,
	NOACK = 1
} Ack;

void I2CMaster_init(uint8_t bitRate, uint8_t prescaler);
void I2CMaster_start(unsigned char address, I2CMode mode);
void I2CMaster_stop();
unsigned char I2CMaster_write(unsigned char dat);
unsigned char I2CMaster_read(unsigned char ack);
unsigned char I2CMaster_isTWINT();
unsigned char I2CMaster_isACK();

#endif /* I2CMASTER_H_ */