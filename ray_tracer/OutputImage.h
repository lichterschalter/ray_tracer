/*
 * OutputImage.h
 *
 *  Created on: 13.12.2015
 *      Author: Fabian Türk
 */

#ifndef OUTPUTIMAGE_H_
#define OUTPUTIMAGE_H_

#include <string>


class OutputImage{
	OutputImage( const OutputImage& ){ };
	OutputImage& operator=( const OutputImage& ){ return *this; };
public:
	OutputImage() { };
	virtual ~OutputImage(){ };
	virtual void createOutput( std::string fileName, int width, int height ) = 0;
};



#endif /* OUTPUTIMAGE_H_ */
