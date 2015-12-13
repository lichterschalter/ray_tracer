/*
 * OutputImage.h
 *
 *  Created on: 13.12.2015
 *      Author: rustong_pu
 */

#ifndef OUTPUTIMAGE_H_
#define OUTPUTIMAGE_H_

#include <string>
using namespace std;

class OutputImage{
	OutputImage( const OutputImage& ){ };
	OutputImage& operator=( const OutputImage& ){ return *this; };
public:
	OutputImage() { };
	virtual ~OutputImage(){ };
	virtual void createOutput( string fileName, int width, int height ) = 0;
};



#endif /* OUTPUTIMAGE_H_ */
