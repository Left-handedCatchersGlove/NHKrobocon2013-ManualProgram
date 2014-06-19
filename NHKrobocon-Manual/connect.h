/*
 * connect.h
 *
 * Created: 2012/08/19 23:12:30
 *  Author: Katsuya
 */ 

#ifndef CONNECT_H_
#define CONNECT_H_

// 足回りモータ
void connect_legmotor( AllMotorStatus * motordata );
// リーフアーム・サイド
void connect_leafArmSideAndHide_motor( AllMotorStatus * motordata );
// リーフアーム・ハンド
void connect_leafArmExtendAndCatch_motor( AllMotorStatus * motordata );
// ファッキンアーム
void connect_fuckinArmMotor( AllMotorStatus * motordata );
// 射出
void connect_shootingMotor( AllMotorStatus * motordata );
// すべての接続関数
void connectAllSlave( AllMotorStatus * motordata );
// すべてのスレーブをリセット
void connectAllSlaveReset( AllMotorStatus * motordata );

#endif /* CONNECT_H_ */