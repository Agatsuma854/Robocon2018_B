/*SerialCtrl_v3.cpp*/
#include "MyLib/SerialCtrlA_v3.h"

//////////////////
//パブリック関数
SerialCtrl::SerialCtrl(Serial *sp){// 宣言時にserialのポインタ持ってくるよう
	_serial = sp;
	cleanArray();
}

void SerialCtrl::setBaud(){// ボーレートの指定用
	setBaud(38400);
}
void SerialCtrl::setBaud(int a){
	_serial->baud(a);
}

bool SerialCtrl::get(){ // コントローラの値を全て配列に代入
	for(int i = 0;i < MISS_MAX;i++){
		if(input() == LEAD){
			for(int k = 0;k < 10;k++){
				data[k] = input();
			}
			if(SUMcheck()){
				//setStr();
				_Func();
				return true;
			}
		}
	}
	_FailFunc();
	return false;
}

unsigned char SerialCtrl::getData(int a){// コントローラのデータを出力
	if((a >= LX)&&(a <= BA2)){
		return data[a];
	}else{
		return 0;
	}
}

void SerialCtrl::Func( void (*func)(void) ) {// 通信成功時に実行するメイン関数の関数をかくのう
	_Func = func;
}

void SerialCtrl::FailFunc( void (*func)(void) ) {// 通信失敗時に実行するメイン関数の関数をかくのう
	_FailFunc = func;
}

////////////////////////////////
// プライベート関数
unsigned char SerialCtrl::input(){ // データの入力を管理
	timer.start();
	timer.reset();
	while(timer.read_ms() < TIME_MAX){
		if(_serial->readable()){
			return _serial->getc();
		}
	}
	return 0;
}

bool SerialCtrl::SUMcheck(){// SUMチェック
	sum = 0;
	for(int jk = 0;jk < 8;jk++){
		sum += data[jk];
	}
	if(sum == data[8] && data[9] == END){
		return true;
	}

	return false;
}
