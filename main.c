/*
 * NHKrobocon_Manual.c
 *
 * Created: 2012/12/03 10:21:36
 *  Author: Katsuya
 */

#include <avr/io.h>
#include "I2CMaster.h"
#include "pspad.h"

#include "slave_address.h"    // スレーブアドレス
#include "motor_structure.h"  // モータの構造体
#include "connect.h"          // スレーブ通信用の関数

#include "action_leg.h"       // 足回りモータの関数
#include "action_leafArm.h"   // リーフアームモータの関数
#include "action_fuckinArm.h" // ファッキンアームの関数
#include "action_shooting.h"  // 発射機構の関数

volatile AllMotorStatus motordata;     // 構造体の宣言

char legFlg = 0;              // 足回り用のフラグ

char fuckinFlg = 0;           // ファッキンアーム用のフラグ
char pre_switch_fuckinArm = 1;// ファッキンアーム用の変数（過去）
char now_switch_fuckinArm = 0;// ファッキンアーム用の変数（未来）

char leafFlg = 0;             // リーフアーム用のフラグ
char pre_switch_leafArm = 1;  // リーフアーム用の変数（過去） 
char now_switch_leafArm = 0;  // リーフアーム用の変数（未来）

int main(void)
{
  // PSコントローラの定義
  PsPin psPin;
  PsPad psdata;
  // PORTの設定
  DDRD  = 0xDF;
  PORTD = 0x30;
  DDRC  = 0xFF;
  PORTC = 0x00;
  // PINの設定
  psPin.port = &PORTD;
  psPin.pin  = &PIND;
  psPin.dat  = PIND5;
  psPin.cmd  = PIND2;
  psPin.sel  = PIND4;
  psPin.clk  = PIND3;

  // I2CMasterの初期設定
  I2CMaster_init( 2, I2CMaster_PRESCALER_16 );
  
  // 初期スピードを0にする
  motordata.leg_motor_left.speed  = 0;
  motordata.leg_motor_right.speed = 0;
  connect_legmotor( &motordata );
  
  leafFlg = 2;
  
  while(1){
    psdata = connectPad( &psPin );  // PSコントローラーからのコマンドを受け取る
    
    /*----- 足回り -----*/
    // 低速、高速切替
    if( psdata.key2.R2 ) { // R2を押し続けているときだけ低速モード
      PORTC &= 0xF0;
      legFlg = 1;
      PORTC |= 0xF6;
    }
    else {
      PORTC &= 0xF0;
      legFlg = 0;
      PORTC |= 0xF9;
    }
    // 前後
    if(      psdata.analogRightHide > 252 ) leg_motor_Prototype( &motordata, legFlg );
    else if( psdata.analogRightHide < 3 )   back_legmotor( &motordata, legFlg );
    // 旋回
    else if( psdata.analogLeftSide > 252 )  turn_right_legmotor( &motordata );
    else if( psdata.analogLeftSide < 3 )    turn_left_legmotor( &motordata );
    else stop_legmotor( &motordata );
    
    /*----- LeafArm -----*/
    pre_switch_leafArm = now_switch_leafArm; // 前回のスイッチ状態を記録する
     
    // 左右に動く
    if( psdata.key1.LEFT  && psdata.key2.triangle ) {
      now_switch_leafArm = 1;
    }
    else now_switch_leafArm = 0;
    
    /* リーフアームチャタリング防止 */
    if( pre_switch_leafArm && !now_switch_leafArm ) {
      leafFlg++;
      if( leafFlg >= 2 ) leafFlg = 0;
    }
    
    if(      psdata.key1.UP    && psdata.key2.triangle ) leafArmHide_down( &motordata );
    else if( psdata.key1.DOWN  && psdata.key2.triangle ) leafArmHide_up( &motordata );
    else {
     leafArmHide_stop( &motordata );
     leafArmSide_stop( &motordata, leafFlg );
    }
    
    // Extend
    if(      psdata.key2.R1    &&  psdata.key2.triangle ) leafArmExtend_extend( &motordata );
    else if( psdata.key2.R2    &&  psdata.key2.triangle ) leafArmExtend_shrink( &motordata );
    // Catch
    else if( psdata.key2.L1    &&  psdata.key2.triangle ) leafArmHandCatch_catch( &motordata );
    else if( psdata.key2.L2    &&  psdata.key2.triangle ) leafArmHandCatch_release( &motordata );
    else {
      leafArmExtend_stop( &motordata );
      leafArmHandCatch_stop( &motordata );
    }
    
    /*----- FuckinArm -----*/
    /*pre_switch_fuckinArm = now_switch_fuckinArm; // 前回のスイッチ状態を記録する
    // ファッキンアームの上下
    if( psdata.key1.UP &&  psdata.key2.R1 ){
      now_switch_fuckinArm = 1;     // フラグを立てる
    }
    else now_switch_fuckinArm = 0;  // 次のループでフラグ回収
     
    if( pre_switch_fuckinArm && !now_switch_fuckinArm) {
      fuckinFlg++;
      if( fuckinFlg >= 2 ) fuckinFlg = 0;
    }*/
    
    if(      psdata.key1.LEFT  &&  psdata.key2.R1 ) fuckinArm_catch( &motordata );
    else if( psdata.key1.RIGHT &&  psdata.key2.R1 ) fuckinArm_release( &motordata );
	  else if( psdata.key1.UP    &&  psdata.key2.R1 ) fuckinArm_up( &motordata );
	  else if( psdata.key1.DOWN  &&  psdata.key2.R1)  fuckinArm_down( &motordata );
    else fuckinArm_stop( &motordata, fuckinFlg );
    
    /*----- 射出機構 -----*/
    if( psdata.key1.START ) shoot( &motordata );
    else if( psdata.key1.SELECT ) plantLoading( &motordata );
    else {
      shoot_stop( &motordata );
      plantLoading_stop( &motordata );
    }
  }
}