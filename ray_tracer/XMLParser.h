/*
 * XMLParser.h
 *
 *  Created on: 19.12.2015
 *      Author: Fabian Türk
 */

#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <string>

class XMLParser{
	std::string inputFilePath;
	std::string outputFileName;
	glm::vec4 posCamera;
	glm::vec4 upCamera;
	glm::vec4 lookAtCamera;
	double horizontal_fov;
	int maxBounces;
	int heightImgPlane;
	int widthImgPlane;
	glm::vec3 bgcolor;

	XMLParser( const XMLParser& xmlParser );
	XMLParser& operator=( const XMLParser& xmlParser );
public:
	XMLParser( std::string inputFilePath );
	~XMLParser( );
	void loadScene( );
	void print( );
};



#endif /* XMLPARSER_H_ */
