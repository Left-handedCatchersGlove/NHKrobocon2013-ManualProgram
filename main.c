/*
 * NHKrobocon_Manual.c
 *
 * Created: 2012/12/03 10:21:36
 *  Author: Katsuya
 */

#include <avr/io.h>
#include "I2CMaster.h"
#include "pspad.h"

#include "slave_address.h"    // �X���[�u�A�h���X
#include "motor_structure.h"  // ���[�^�̍\����
#include "connect.h"          // �X���[�u�ʐM�p�̊֐�

#include "action_leg.h"       // ����胂�[�^�̊֐�
#include "action_leafArm.h"   // ���[�t�A�[�����[�^�̊֐�
#include "action_fuckinArm.h" // �t�@�b�L���A�[���̊֐�
#include "action_shooting.h"  // ���ˋ@�\�̊֐�

volatile AllMotorStatus motordata;     // �\���̂̐錾

char legFlg = 0;              // �����p�̃t���O

char fuckinFlg = 0;           // �t�@�b�L���A�[���p�̃t���O
char pre_switch_fuckinArm = 1;// �t�@�b�L���A�[���p�̕ϐ��i�ߋ��j
char now_switch_fuckinArm = 0;// �t�@�b�L���A�[���p�̕ϐ��i�����j

char leafFlg = 0;             // ���[�t�A�[���p�̃t���O
char pre_switch_leafArm = 1;  // ���[�t�A�[���p�̕ϐ��i�ߋ��j 
char now_switch_leafArm = 0;  // ���[�t�A�[���p�̕ϐ��i�����j

int main(void)
{
  // PS�R���g���[���̒�`
  PsPin psPin;
  PsPad psdata;
  // PORT�̐ݒ�
  DDRD  = 0xDF;
  PORTD = 0x30;
  DDRC  = 0xFF;
  PORTC = 0x00;
  // PIN�̐ݒ�
  psPin.port = &PORTD;
  psPin.pin  = &PIND;
  psPin.dat  = PIND5;
  psPin.cmd  = PIND2;
  psPin.sel  = PIND4;
  psPin.clk  = PIND3;

  // I2CMaster�̏����ݒ�
  I2CMaster_init( 2, I2CMaster_PRESCALER_16 );
  
  // �����X�s�[�h��0�ɂ���
  motordata.leg_motor_left.speed  = 0;
  motordata.leg_motor_right.speed = 0;
  connect_legmotor( &motordata );
  
  leafFlg = 2;
  
  while(1){
    psdata = connectPad( &psPin );  // PS�R���g���[���[����̃R�}���h���󂯎��
    
    /*----- ����� -----*/
    // �ᑬ�A�����ؑ�
    if( psdata.key2.R2 ) { // R2�����������Ă���Ƃ������ᑬ���[�h
      PORTC &= 0xF0;
      legFlg = 1;
      PORTC |= 0xF6;
    }
    else {
      PORTC &= 0xF0;
      legFlg = 0;
      PORTC |= 0xF9;
    }
    // �O��
    if(      psdata.analogRightHide > 252 ) leg_motor_Prototype( &motordata, legFlg );
    else if( psdata.analogRightHide < 3 )   back_legmotor( &motordata, legFlg );
    // ����
    else if( psdata.analogLeftSide > 252 )  turn_right_legmotor( &motordata );
    else if( psdata.analogLeftSide < 3 )    turn_left_legmotor( &motordata );
    else stop_legmotor( &motordata );
    
    /*----- LeafArm -----*/
    pre_switch_leafArm = now_switch_leafArm; // �O��̃X�C�b�`��Ԃ��L�^����
     
    // ���E�ɓ���
    if( psdata.key1.LEFT  && psdata.key2.triangle ) {
      now_switch_leafArm = 1;
    }
    else now_switch_leafArm = 0;
    
    /* ���[�t�A�[���`���^�����O�h�~ */
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
    /*pre_switch_fuckinArm = now_switch_fuckinArm; // �O��̃X�C�b�`��Ԃ��L�^����
    // �t�@�b�L���A�[���̏㉺
    if( psdata.key1.UP &&  psdata.key2.R1 ){
      now_switch_fuckinArm = 1;     // �t���O�𗧂Ă�
    }
    else now_switch_fuckinArm = 0;  // ���̃��[�v�Ńt���O���
     
    if( pre_switch_fuckinArm && !now_switch_fuckinArm) {
      fuckinFlg++;
      if( fuckinFlg >= 2 ) fuckinFlg = 0;
    }*/
    
    if(      psdata.key1.LEFT  &&  psdata.key2.R1 ) fuckinArm_catch( &motordata );
    else if( psdata.key1.RIGHT &&  psdata.key2.R1 ) fuckinArm_release( &motordata );
	  else if( psdata.key1.UP    &&  psdata.key2.R1 ) fuckinArm_up( &motordata );
	  else if( psdata.key1.DOWN  &&  psdata.key2.R1)  fuckinArm_down( &motordata );
    else fuckinArm_stop( &motordata, fuckinFlg );
    
    /*----- �ˏo�@�\ -----*/
    if( psdata.key1.START ) shoot( &motordata );
    else if( psdata.key1.SELECT ) plantLoading( &motordata );
    else {
      shoot_stop( &motordata );
      plantLoading_stop( &motordata );
    }
  }
}