/*
 * XMLParser.cpp
 *
 *  Created on: 19.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include <string>
#include "../libs/pugixml-1.7/src/pugixml.hpp"
#include "../libs/pugixml-1.7/src/pugixml.cpp"
#include "XMLParser.h"
using namespace std;


XMLParser::XMLParser( const XMLParser& XMLParser ){ }
XMLParser& XMLParser::operator=( const XMLParser& XMLParser ){ return *this; }
XMLParser::XMLParser( string filename ){
	this->fileName = fileName;
}
XMLParser::~XMLParser( ){ }

void XMLParser::loadScene( ){

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file( "../scenes/example1.xml" );
	std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("scene").attribute("output_file").value() << std::endl;

}

