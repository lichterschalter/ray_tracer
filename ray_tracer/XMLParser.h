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

	XMLParser( const XMLParser& XMLParser );
	XMLParser& operator=( const XMLParser& XMLParser );
public:
	XMLParser( std::string inputFilePath );
	~XMLParser( );
	void loadScene( );
};



#endif /* XMLPARSER_H_ */
