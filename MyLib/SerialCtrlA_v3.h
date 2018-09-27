/*
 * SerialCtrl_v3.h
 *
 *  Created on: May 4, 2018
 *      Author: AGATSUMA
 *
 *  READ!!
 *  この関数はメイン関数側で"serial"を宣言して置き,そのポインタを受け取ることで楽にsumcheckなどが
 *  できる仕様になっています
 *
 *	v2_作動確認済み完成版
 *
 *  v3_データを構造体に格納して利便性の向上をはかる
 */

#ifndef MYLIB_SERIALCTRL_V3_H_
#define MYLIB_SERIALCTRL_V3_H_
#include "mbed.h"

/*		マクロ(つぶすときは置き換えろ)		*/
enum {
	LX, LY, RX, RY, L2, R2, BA1, BA2, SUM
};
//データ位置
#define TRIANGLE (0x01 << 0)
#define CIRCLE   (0x01 << 1)
#define CROSS    (0x01 << 2)
#define SQUARE   (0x01 << 3)
#define UP       (0x01 << 4)
#define RIGHT    (0x01 << 5)
#define DOWN     (0x01 << 6)
#define LEFT     (0x01 << 7)

#define L1     (0x01 << 0)
#define L3     (0x01 << 1)
#define R1     (0x01 << 2)
#define R3     (0x01 << 3)
#define SELECT (0x01 << 4)
#define START  (0x01 << 5)
#define PS     (0x01 << 6)

//その他
#define MISS_MAX 32 // FEPの設定変えたので多めのマージンを
#define TIME_MAX 16
#define LEAD 0xAF
#define END 0xED

/*Assign
 Serial
 |-------|---------------|----------------------
 | Byte  |     Data      | Information
 |-------|---------------|----------------------
 | 0Byte |     0xAF      | Start Germany:Anfang
 | 1Byte | unsigned char | LStick X
 | 2Byte | unsigned char | LStick Y
 | 3Byte | unsigned char | RStick X
 | 4Byte | unsigned char | RStick Y
 | 5Byte | unsigned char | L2
 | 6Byte | unsigned char | R2
 | 7Byte | unsigned char | ButtonAssign1
 | 8Byte | unsigned char | ButtonAssign2
 | 9Byte | unsigned char | CheckSUM
 |10Byte |     0xED      | End Germany:Ende
 |-------|---------------|----------------------

 7Byte ButtonAssign
 |-------|--------|-------------
 |  Bit  |  Data  | Information
 |-------|--------|-------------
 | 0Bit  |  i/o   |  TRIANGLE
 | 1Bit  |  i/o   |  CIRCLE
 | 2Bit  |  i/o   |  CROSS
 | 3Bit  |  i/o   |  SQUARE
 | 4Bit  |  i/o   |  UP
 | 5Bit  |  i/o   |  RIGHT
 | 6Bit  |  i/o   |  DOWN
 | 7Bit  |  i/o   |  LEFT
 |-------|--------|-------------

 8Byte ButtonAssign
 |-------|--------|-------------
 |  Bit  |  Data  | Information
 |-------|--------|-------------
 | 0Bit  |  i/o   |  L1
 | 1Bit  |  i/o   |  L3
 | 2Bit  |  i/o   |  R1
 | 3Bit  |  i/o   |  R3
 | 4Bit  |  i/o   |  SELECT
 | 5Bit  |  i/o   |  START
 | 6Bit  |  i/o   |  PS
 | 7Bit  |  i/o   |  -
 |-------|--------|-------------
 */

class SerialCtrl {
public:
	SerialCtrl(Serial *sp);

	//関数の定義
	void setBaud();	// ボーレート指定 ( 38400 )
	void setBaud(int a); // 引数ありボーレート指定
	bool get(void); // 通信を確認と値の取り出し用
	unsigned char getData(int a); // データの入手 必要性に　疑問符

	//ユーティリティ(LEDの点灯用)
	void Func(void (*func)(void));
	void FailFunc(void (*func)(void));

private:

	// 宣言
	Serial *_serial;	// シリアルクラスのポインタ
	Timer timer;			// 通信観測用のタイマー

	int timeoutNum;		// タムアウト回数測定
	unsigned char sum;	// サムチェック用
	unsigned char data[10];	//データ格納

	void (*_Func)(void);     //通信成功時実行関数ポインタ
	void (*_FailFunc)(void); //通信失敗時実行関数ポインタ

	// プライベート関数
	void cleanArray(void) { // 配列の初期化(インライン)
		for (int a = 0; a < 10; a++) {
			data[a] = 0;
		}
	}
	bool SUMcheck();
	unsigned char input();
	void setStr();
};

#endif
