/*
 * OutputImage.h
 *
 *  Created on: 13.12.2015
 *      Author: rustong_pu
 */

#ifndef OUTPUTIMAGE_H_
#define OUTPUTIMAGE_H_

using namespace std;

class OutputImage{
	OutputImage( const OutputImage& ){ };
	OutputImage& operator=( const OutputImage& ){ return *this; };
public:
	OutputImage() { };
	virtual ~OutputImage(){ };
	virtual void createOutput() = 0;
};



#endif /* OUTPUTIMAGE_H_ */
