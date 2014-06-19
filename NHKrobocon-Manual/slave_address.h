/*
 * slave_address.h
 *
 * Created: 2012/08/09 17:02:45
 *  Author: Katsuya
 */ 

#ifndef SLAVE_ADDRESS_H_
#define SLAVE_ADDRESS_H_

/*--- 足回りモータ ---*/
static const uint8_t LEG_MOTOR_ADDRESS = 0x01;

/*--- リーフアーム ---*/
static const uint8_t LEAFARM_MOTOR_SIDEHIDE_ADDRESS = 0x02;
static const uint8_t LEAFARM_MOTOR_EXTENDCATCH_ADDRESS = 0x03;

/*--- ファッキンアーム ---*/
static const uint8_t FUCKINARM_MOTOR_ADDRESS = 0x04;

/*--- 射出機構 ---*/
static const uint8_t SHOOTING_MOTOR_ADDRESS = 0x05;

#endif /* SLAVE_ADDRESS_H_ */