/*
 * MoveCtrl.h
 *
 *  Created on: Jul 18, 2018
 *      Author: AGATSUMA
 *
 *      無能なのでpinたちのポインタを持ってくることで実装予定
 */

#ifndef MYLIB_MOVECTRLA_V1_H_
#define MYLIB_MOVECTRLA_V1_H_

#include "mbed.h"

class MoveCtrl{
private:
	//ポインタ宣言
	PwmOut *_P[4];// モーター制御用Pwmポインタ
	DigitalOut *_D[4];// モータードライバー制御用DigitalOutポインタ

	//制御変数
	float Angle; //0~180,0~-180を格納
	float PwmPow; // PWMの強さ指定
	float PwmGain; // Pwmの強さ調整
	int Lx,Ly;
	int ModeSelect; //制御モード変更変数

	//その他
	void MkValue();

public:
	MoveCtrl(PwmOut *p1, PwmOut *p2, DigitalOut *d1, DigitalOut *d2);// 初期化設定x4
	MoveCtrl(PwmOut *p1, PwmOut *p2, DigitalOut *d1, DigitalOut *d2, int m);
	MoveCtrl(PwmOut *p1, PwmOut *p2, PwmOut *p3, PwmOut *p4, DigitalOut *d1, DigitalOut *d2, DigitalOut *d3, DigitalOut *d4);
	MoveCtrl(PwmOut *p1, PwmOut *p2, PwmOut *p3, PwmOut *p4, DigitalOut *d1, DigitalOut *d2, DigitalOut *d3, DigitalOut *d4,int m);

	void setPwmGain(float g);
	void move();
};

#endif /* MYLIB_MOVECTRLA_V1_H_ */

/*メカナム全方位制御の理屈
 * 作り変えて面倒なのでまだ書いてない
 * 動かし方の都合で全方位・旋回・横旋回移動がセットになってるのは確か

 * モーター配置
 ・メカナム 二輪配置 (実装作業中) mode 0
	[2]───────[1]
	 │         │
	 │    ↑    │
	 │         │
	[-]───────[-]

   ・メカナム or オムニX字配置 (未実装) mode 1 / 2
	[2]───────[1]
	 │         │
	 │    ↑    │
	 │         │
	[3]───────[4]

   ・オムニ十字配置 (未実装) mode 3
	 ┌───[1]───┐
	 │         │
	[2]   ↑   [4]
     │         │
     └───[3]───┘

 */
