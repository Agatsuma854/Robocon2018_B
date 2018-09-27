/*
 * MoveCtrl.cpp
 *
 *  Created on: Jul 18, 2018
 *      Author: AGATSUMA
 */
#include "MyLib/MoveCtrlA_v1.h"

MoveCtrl::MoveCtrl(PwmOut *p1,PwmOut *p2,DigitalOut *d1,DigitalOut *d2){
	MoveCtrl(p1,p2,p1,p2,d1,d2,d1,d2,0);
}

MoveCtrl::MoveCtrl(PwmOut *p1,PwmOut *p2,DigitalOut *d1,DigitalOut *d2,int m){
	MoveCtrl(p1,p2,p1,p2,d1,d2,d1,d2,m);
}

MoveCtrl::MoveCtrl(PwmOut *p1, PwmOut *p2, PwmOut *p3, PwmOut *p4, DigitalOut *d1, DigitalOut *d2, DigitalOut *d3, DigitalOut *d4){
	MoveCtrl(p1,p2,p3,p4,d1,d2,d3,d4,1);
}

MoveCtrl::MoveCtrl(PwmOut *p1, PwmOut *p2, PwmOut *p3, PwmOut *p4, DigitalOut *d1, DigitalOut *d2, DigitalOut *d3, DigitalOut *d4,int m){
	ModeSelect = m;

	_P[0] = p1;
	_P[1] = p2;
	_P[2] = p3;
	_P[3] = p4;
	_D[0] = d1;
	_D[1] = d2;
	_D[2] = d3;
	_D[3] = d4;
}

void MoveCtrl::MkValue(){
	Angle = atan2((float)(Ly - 128),(float)(Lx - 128)) * 180.0 / M_PI;
	PwmPow = hypotf(Lx,Ly) / 128.0;
}
