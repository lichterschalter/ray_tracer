/*
 * XMLParser.cpp
 *
 *  Created on: 19.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include <string>
#include <vector>
#include "../libs/pugixml-1.7/src/pugixml.hpp"
#include "../libs/pugixml-1.7/src/pugixml.cpp"
#include "XMLParser.h"
using namespace std;


XMLParser::XMLParser( const XMLParser& XMLParser ){ }
XMLParser& XMLParser::operator=( const XMLParser& XMLParser ){ return *this; }
XMLParser::XMLParser( string fileName ){
	this->fileName = fileName;
}
XMLParser::~XMLParser( ){ }

void XMLParser::loadScene( ){

	std::vector<char> fileNameConst(fileName.begin(), fileName.end());
	fileNameConst.push_back('\0');
	char* fileNamePointer = &fileNameConst[ 0 ];


	// get the char* using &writable[0] or &*writable.begin()

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file( fileNamePointer );


	if (result)
	{
		std::cout << "Load result: " << result.description() << ", output file: " << doc.child("scene").attribute("output_file").value() << std::endl;	}
	else
	{
	    std::cout << "XML [" << fileNamePointer << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
	    std::cout << "Error description: " << result.description() << "\n";
	    std::cout << "Error offset: " << result.offset << " (error at [..." << ("../scenes/example1.xml" + result.offset) << "]\n\n";
	}

}

