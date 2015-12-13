/*
 * OutputPPM.h
 *
 *  Created on: 13.12.2015
 *      Author: rustong_pu
 */

#ifndef OUTPUTPPM_H_
#define OUTPUTPPM_H_

#include "OutputImage.h"
using namespace std;

class OutputPPM : public OutputImage{
	OutputPPM( const OutputPPM& ){ };
	OutputPPM& operator=( const OutputPPM& ){ return *this; };
public:
	OutputPPM() { };
	virtual ~OutputPPM();
	virtual void createOutput();
};



#endif /* OUTPUTPPM_H_ */
