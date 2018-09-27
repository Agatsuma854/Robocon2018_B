/*
 * COM.h
 *
 *  Created on: Sep 2, 2018
 *      Author: Mayoi
 */

#ifndef COM_COM_H_
#define COM_COM_H_
#include "mbed.h"

class COM : public Serial{
private:
	//
	Timer timer,serTimer;
	// メンバ定数 以下 オブジェクト生成時に引数で指定
	const unsigned char MSB = 0xAF; // 最上位ビット
	const unsigned char LSB = 0xED; // 最下位ビット
	const int TIME_OUT = 24;
	const int SER_TIME_OUT = 12;
	const int MISS_MAX = 24;
	//　メンバ変数
	unsigned char data[9];
	unsigned char sumCheck;
	bool serFlg_m;
	int missCounter_m;
	// メンバ関数
	void serProsses();
	unsigned char serInput(); // データ取り出し用
	bool sumcheck(); // サムチェック用
public:
	bool comable(); // 通信できているか0/1で返す

	// コンストラクタ
	COM(PinName serTx,PinName serRx);
	COM(PinName serTx,PinName serRx,int serBaul);
};

#endif /* COM_COM_H_ */

/*ButtonAssign
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
