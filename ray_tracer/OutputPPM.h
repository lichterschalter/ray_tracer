/*
 * OutputPPM.h
 *
 *  Created on: 13.12.2015
 *      Author: Fabian Türk
 */

#ifndef OUTPUTPPM_H_
#define OUTPUTPPM_H_

#include <string>
#include "OutputImage.h"

class OutputPPM : public OutputImage{
	OutputPPM( const OutputPPM& );
	OutputPPM& operator=( const OutputPPM& );
public:
	OutputPPM();
	virtual ~OutputPPM();
	virtual void createOutput( std::string fileName, std::string content, int width, int height );
};



#endif /* OUTPUTPPM_H_ */
