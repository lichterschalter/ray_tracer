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
XMLParser::XMLParser( string inputFilePath ){
	this->inputFilePath = inputFilePath;
}
XMLParser::~XMLParser( ){ }

void XMLParser::loadScene( ){

	std::vector<char> inputFilePathConst(inputFilePath.begin(), inputFilePath.end());
	inputFilePathConst.push_back('\0');
	char* inputFilePathPointer = &inputFilePathConst[ 0 ];


	// get the char* using &writable[0] or &*writable.begin()

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file( inputFilePathPointer );


	if (result)
	{
		std::cout << "Load result: " << result.description() << ", output file: " << doc.child("scene").attribute("output_file").value() << std::endl;	}
	else
	{
	    std::cout << "XML [" << inputFilePathPointer << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
	    std::cout << "Error description: " << result.description() << "\n";
	    std::cout << "Error offset: " << result.offset << " (error at [..." << (inputFilePathPointer + result.offset) << "]\n\n";
	}



	for (pugi::xml_node tool = doc.child("scene").child("background_color"); tool; tool = tool.next_sibling("background_color"))
	{
	    std::cout << "r: " << tool.attribute("r").as_float() << endl;
	    std::cout << "g: " << tool.attribute("g").as_float() << endl;
	    std::cout << "b: " << tool.attribute("b").as_float() << endl;
	}



}

