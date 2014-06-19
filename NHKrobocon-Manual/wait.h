/*
 * wait.h
 *
 *  Created on: 2011/01/17
 *  @file   wait.h
 *  @author Hirokazu Yokoyama
 *  @date   2011/01/17
 */

#ifndef WAIT_H_
#define WAIT_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif  /* F_CPU */

#include <util/delay.h>

/**
 * マイクロ秒待機
 * @param   usec    マイクロ秒
 * */
void waitMicrosec(unsigned int usec) {
    while(--usec) {
        _delay_us(1);
    }
}

/***
 * ミリ秒待機
 * @param   msec    ミリ秒
 * */
void waitMillisec(unsigned int msec) {
    while(--msec) {
        _delay_ms(1);
    }
}



#endif /* WAIT_H_ */
