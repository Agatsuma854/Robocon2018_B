/*
 * vCOM.cpp
 *
 *  Created on: Sep 2, 2018
 *      Author: Mayoi
 */
#include "COM.h"

/// Public /////////////////////////////////////////////////////////////////
bool COM::comable(){
	if( (timer.read_ms() < TIME_OUT) && serFlg_m) return true;
	return false;
}

// コンストラクタ //
COM::COM(PinName serTx, PinName serRx) : Serial(serTx,serRx){
	COM(serTx, serRx, 38400);
}

COM::COM(PinName serTx, PinName serRx, int serBaul) : Serial(serTx,serRx){
	for(int i = 0;i < 8;i++){
		data[i] = 0;
	}
	baud(serBaul);
	attach(&serProsses, Serial::RxIrq);
	timer.start();
	timer.reset();
}//
/// Private ////////////////////////////////////////////////////////////////
void COM::serProsses(){
	missCounter_m = 0;
	for(missCounter_m = 0;missCounter_m < MISS_MAX;missCounter_m++){
		if(serInput() == MSB){
			missCounter_m = 0;
			for(missCounter_m = 0;missCounter_m < 9;missCounter_m++){
				data[missCounter_m] = serInput();
			}
			if(sumcheck() && (serInput() == LSB) ){
				serFlg_m = true;
				timer.start();
				timer.reset();
			}else{
				serFlg_m = false;
			}
		}
	}
}

unsigned char COM::serInput(){
	serTimer.start();
	serTimer.reset();
	while(serTimer.read_ms() < SER_TIME_OUT){
		if(readable()) return getc();
		return 0;
	}
	return 0;
}

bool COM::sumcheck(){
	sumCheck = 0;
	for(int s = 0;s < 8;s++){
		sumCheck += data[s];
	}
	if(sumCheck == data[8])
		return true;
	return false;
}
