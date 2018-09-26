/*
 * SimulProcessor.h
 *
 *  Created on: Sep 27, 2018
 *      Author: Mayoi
 */

#ifndef MOVE_SIMULPROCESSOR_H_
#define MOVE_SIMULPROCESSOR_H_

class SimulProcessor {
private:
	int indefNum;
public:
	SimulProcessor(); // (式の個数)
	virtual ~SimulProcessor();

	void processSimul(int xNum,double *p); // 配列のポインタとこうの数
};

#endif /* MOVE_SIMULPROCESSOR_H_ */
