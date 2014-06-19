/*
 * pspad.h
 *
 * Created: 2012/12/03 10:21:36
 *  Author: Katsuya
 */

#ifndef PSPAD_H_
#define PSPAD_H_

#include <avr/io.h>
#include "wait.h"

typedef struct PsPin {
    volatile uint8_t *port;
    volatile uint8_t *pin;
    unsigned int dat : 8;
    unsigned int cmd : 8;
    unsigned int sel : 8;
    unsigned int clk : 8;
} PsPin;

typedef union PsPadKey1 {
    unsigned int byteKey : 8;
    struct {
        unsigned int SELECT : 1;
        unsigned int L3 : 1;
        unsigned int R3 : 1;
        unsigned int START : 1;
        unsigned int UP : 1;
        unsigned int RIGHT : 1;
        unsigned int DOWN : 1;
        unsigned int LEFT : 1;
    };
} PsPadKey1;


typedef union PsPadKey2 {
    unsigned int byteKey : 8;
    struct {
        unsigned int L2 : 1;
        unsigned int R2 : 1;
        unsigned int L1 : 1;
        unsigned int R1 : 1;
        unsigned int triangle : 1;
        unsigned int circle : 1;
        unsigned int cross : 1;
        unsigned int square : 1;
    };
} PsPadKey2;

/**
 * PSコントローラから取得する値
 * */
typedef struct PsPad {
    // コントローラの種類
    unsigned int id : 8;
    unsigned int chk : 8;
    // | 左 | 下 | 右 | 上 | START | SELECT | R3 | L3 | SELECT |
    PsPadKey1 key1;
    // | □ | × | ○ | △ | R1 | L1 | R2 | L2 |
    PsPadKey2 key2;
    unsigned int analogRightSide : 8;
    unsigned int analogRightHide : 8;
    unsigned int analogLeftSide : 8;
    unsigned int analogLeftHide : 8;
} PsPad;

/**
 * PSコントローラの種類
 * */
typedef enum PsPadId {
    NOMAL_PAD = 0x41,
    ANALOG_PAD = 0x73,
    ANALOG_JOY_PAD = 0x53
} PsPadId;

PsPad connectPad(PsPin *pin);
int rcvdat(int cmd);

static PsPin psPin;

/**
 * PSコントローラの入力されているキーを取得する
 * @return  入力された値
 * */
PsPad connectPad(PsPin *pin) {
    psPin = *pin;
    PsPad pad;
    *psPin.port &= ~_BV(psPin.sel);
    waitMillisec(10);

    rcvdat(0x01);
    pad.id = rcvdat(0x42);
    pad.chk = rcvdat(0x00);
    pad.key1.byteKey = ~rcvdat(0x00);
    pad.key2.byteKey = ~rcvdat(0x00);
    pad.analogRightSide = rcvdat(0x00);
    pad.analogRightHide = rcvdat(0x00);
    pad.analogLeftSide = rcvdat(0x00);
    pad.analogLeftHide = rcvdat(0x00);
    waitMicrosec(10);

    *psPin.port |= _BV(psPin.sel);
    waitMillisec(10);

    return pad;
}


/**
* コマンドを投げてデータを貰う。
* @param    cmd    PSコントローラに送るコマンド
* @return   PSコントローラからの信号
* */

int rcvdat(int cmd)
{
    int dat=0,i;
    *psPin.port |= _BV(psPin.clk);  // クロックをＨにしておく

    // クロック立下りで出力、立ち上がりで入力
    for(i=0;i<8;i++)
    {
        if((cmd & ~_BV(i)) == cmd) {    // i番目のビットが0かどうかの判別
            *psPin.port &= ~_BV(psPin.cmd);
        } else{
            *psPin.port |= _BV(psPin.cmd);
        }

        waitMicrosec(5);

        // クロックをＬに
        *psPin.port &= ~_BV(psPin.clk);
        waitMicrosec(5);

        if(bit_is_set(*psPin.pin, psPin.dat)){
            dat |= _BV(i);
        } else {
            dat &= ~_BV(i);
        }

        // クロックを進める
        *psPin.port |= _BV(psPin.clk);
    }

    waitMicrosec(5);
    // CMDをＨに
    *psPin.port |= _BV(psPin.cmd);

    return dat;
}

#endif /* PSPAD_H_ */