/*
 * XMLParser.cpp
 *
 *  Created on: 19.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "../libs/glm/glm/gtx/string_cast.hpp"
#include "../libs/pugixml-1.7/src/pugixml.hpp"
#include "../libs/pugixml-1.7/src/pugixml.cpp"
#include "XMLParser.h"
using namespace std;

XMLParser::XMLParser( string inputFilePath ){
	this->inputFilePath = inputFilePath;

	//READ FILE
	std::vector<char> inputFilePathConst(inputFilePath.begin(), inputFilePath.end());
	inputFilePathConst.push_back('\0');
	char* inputFilePathPointer = &inputFilePathConst[ 0 ];
	pugi::xml_parse_result result = doc.load_file( inputFilePathPointer );

	if (result)
	{
		std::cout << "Load result: " << result.description() << ", output file: " << doc.child("scene").attribute("output_file").value() << std::endl;	}
	else
	{
		outputFileName = "example0";
	    std::cout << "XML [" << inputFilePathPointer << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
	    std::cout << "Error description: " << result.description() << "\n";
	    std::cout << "Error offset: " << result.offset << " (error at [..." << (inputFilePathPointer + result.offset) << "]\n\n";
	}

	//READ NODES
	string outputFN = doc.child("scene").child("camera").child("horizontal_fov").attribute("angle").value();
	outputFileName = outputFN.substr(0, outputFN.size() - 4);
	bgcolor = glm::vec3(
			doc.child("scene").child("background_color").attribute("r").as_float(),
			doc.child("scene").child("background_color").attribute("g").as_float(),
			doc.child("scene").child("background_color").attribute("b").as_float()
	);
	posCamera = glm::vec4(
			doc.child("scene").child("camera").child("position").attribute("x").as_float(),
			doc.child("scene").child("camera").child("position").attribute("y").as_float(),
			doc.child("scene").child("camera").child("position").attribute("z").as_float(),
			1.0
	);
	upCamera = glm::vec4(
			doc.child("scene").child("camera").child("up").attribute("x").as_float(),
			doc.child("scene").child("camera").child("up").attribute("y").as_float(),
			doc.child("scene").child("camera").child("up").attribute("z").as_float(),
			1.0
	);
	lookAtCamera = glm::vec4(
			doc.child("scene").child("camera").child("lookat").attribute("x").as_float(),
			doc.child("scene").child("camera").child("lookat").attribute("y").as_float(),
			doc.child("scene").child("camera").child("lookat").attribute("z").as_float(),
			1.0
	);
	horizontal_fov = doc.child("scene").child("camera").child("horizontal_fov").attribute("angle").as_float();
	widthImgPlane = doc.child("scene").child("camera").child("resolution").attribute("horizontal").as_int();
	heightImgPlane = doc.child("scene").child("camera").child("resolution").attribute("vertical").as_int();
	maxBounces = doc.child("scene").child("camera").child("max_bounces").attribute("n").as_int();

}
XMLParser::~XMLParser( ){ }
XMLParser::XMLParser( const XMLParser& xmlParser ){
	this->inputFilePath = xmlParser.inputFilePath;
	this->outputFileName = xmlParser.outputFileName;
	this->posCamera = xmlParser.posCamera;
	this->upCamera = xmlParser.upCamera;
	this->lookAtCamera = xmlParser.lookAtCamera;
	this->horizontal_fov = xmlParser.horizontal_fov;
	this->maxBounces = xmlParser.maxBounces;
	this->heightImgPlane = xmlParser.heightImgPlane;
	this->widthImgPlane = xmlParser.widthImgPlane;
	this->bgcolor = xmlParser.bgcolor;
}
XMLParser& XMLParser::operator=( const XMLParser& xmlParser ){ return *this; }

void XMLParser::print(){
	cout << "bgcolor: " << glm::to_string(bgcolor) << endl;
	cout << "posCamera: " << glm::to_string(posCamera) << endl;
	cout << "upCamera: " << glm::to_string(upCamera) << endl;
	cout << "horizontal_fov: " << horizontal_fov << endl;
	cout << "resolution horizontal: " << widthImgPlane << endl;
	cout << "resolution vertical: " << heightImgPlane << endl;
	cout << "max_bounces: " << maxBounces << endl;
}

vector< vector<float> > XMLParser::dataSpheres( ){

	vector< vector<float> > dataSpheres;
	for (pugi::xml_node tool = doc.child("scene").child("surfaces").child("sphere"); tool; tool = tool.next_sibling("sphere")) {
		dataSpheres.push_back(vector<float>()); // Add one empty row
	}
	for (unsigned int i = 0; i < dataSpheres.size(); ++i ) {
		for( int j = 0; j < 5; ++j ){
			dataSpheres.at( i ).push_back( 0.0 );
		}
	}

	for( unsigned int i = 0; i < dataSpheres.size(); ++i ){
		for( unsigned int j = 0; j < dataSpheres.at( i ).size(); ++j ){
			stringstream sstr;
			sstr << dataSpheres.at(i).at(j);
			cout << sstr.str() << " ";
		}
		cout << endl;
	}
	return dataSpheres;
}

