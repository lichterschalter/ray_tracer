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
		cout << "XML load result: " << result.description() << ", loaded file: \"" << inputFilePath << "\"." << endl;	}
	else
	{
		outputFileName = "example0";
	    cerr << "XML [" << inputFilePathPointer << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
	    cerr << "Error description: " << result.description() << "\n";
	    cerr << "Error offset: " << result.offset << " (error at [..." << (inputFilePathPointer + result.offset) << "]\n\n";
	}

	//READ NODES
	string outputFN = doc.child("scene").attribute("output_file").value();
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
	ambientLight[ 0 ] = doc.child("scene").child("lights").child("ambient_light").child("color").attribute("r").as_float();
	ambientLight[ 1 ] = doc.child("scene").child("lights").child("ambient_light").child("color").attribute("g").as_float();
	ambientLight[ 2 ] = doc.child("scene").child("lights").child("ambient_light").child("color").attribute("b").as_float();
	parallelLightCol[ 0 ] = doc.child("scene").child("lights").child("parallel_light").child("color").attribute("r").as_float();
	parallelLightCol[ 1 ] = doc.child("scene").child("lights").child("parallel_light").child("color").attribute("g").as_float();
	parallelLightCol[ 2 ] = doc.child("scene").child("lights").child("parallel_light").child("color").attribute("b").as_float();
	parallelLightDir[ 0 ] = doc.child("scene").child("lights").child("parallel_light").child("direction").attribute("x").as_float();
	parallelLightDir[ 1 ] = doc.child("scene").child("lights").child("parallel_light").child("direction").attribute("y").as_float();
	parallelLightDir[ 2 ] = doc.child("scene").child("lights").child("parallel_light").child("direction").attribute("z").as_float();

	unsigned int i = 0;
	for (pugi::xml_node tool = doc.child("scene").child("lights"); tool; tool = tool.next_sibling("point_light") ) {
		pointLightsCol.push_back( glm::vec3() ); // Add one empty row
		pointLightsCol.at( i )[ 0 ] = tool.child("color").attribute("r").as_float();
		pointLightsCol.at( i )[ 0 ] = tool.child("color").attribute("g").as_float();
		pointLightsCol.at( i )[ 0 ] = tool.child("color").attribute("b").as_float();
		++i;
	}



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
	this->ambientLight = ambientLight;
	this->parallelLightCol = parallelLightCol;
	this->parallelLightDir = parallelLightDir;
	this->pointLightsCol = pointLightsCol;
	this->pointLightsPos = pointLightsPos;
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
	cout << "ambientLight: " << to_string( ambientLight ) << endl;
	cout << "parallelLightCol: " << to_string( parallelLightCol ) << endl;
	cout << "parallelLightDir: " << to_string( parallelLightDir ) << endl;

	for( unsigned int i = 0; i < pointLightsCol.size(); ++i ){
		stringstream sstr;
		sstr << to_string( pointLightsCol.at( i ) );
		cout << "pointLight" << i + 1 << ": " << sstr.str() << " " << endl;
	}

	for( unsigned int i = 0; i < pointLightsPos.size(); ++i ){
		stringstream sstr;
		sstr << to_string( pointLightsPos.at( i ) );
		cout << sstr.str() << " ";
		cout << endl;
	}

}

vector< vector<float> > XMLParser::dataSpheres( ){

	vector< vector<float> > dataSpheres;
	int i = 0;
	for (pugi::xml_node tool = doc.child("scene").child("surfaces").child("sphere"); tool; tool = tool.next_sibling("sphere")) {
		dataSpheres.push_back(vector<float>()); // Add one empty row

		//radius, posX, posY, posZ, phongKA, phongKD, phongIOF, phongEXP, reflectance, transmittance, refraction
		dataSpheres.at( i ).push_back( tool.attribute("radius").as_float() );
		dataSpheres.at( i ).push_back( tool.child("position").attribute("x").as_float() );
		dataSpheres.at( i ).push_back( tool.child("position").attribute("y").as_float() );
		dataSpheres.at( i ).push_back( tool.child("position").attribute("z").as_float() );
		dataSpheres.at( i ).push_back( tool.child("material_solid").child("color").attribute("r").as_float() );
		dataSpheres.at( i ).push_back( tool.child("material_solid").child("color").attribute("g").as_float() );
		dataSpheres.at( i ).push_back( tool.child("material_solid").child("color").attribute("b").as_float() );
		dataSpheres.at( i ).push_back( tool.child("material_solid").child("phong").attribute("ka").as_float() );
		dataSpheres.at( i ).push_back( tool.child("material_solid").child("phong").attribute("kd").as_float() );
		dataSpheres.at( i ).push_back( tool.child("material_solid").child("phong").attribute("ks").as_float() );
		dataSpheres.at( i ).push_back( tool.child("material_solid").child("phong").attribute("exponent").as_float() );
		dataSpheres.at( i ).push_back( tool.child("material_solid").child("reflectance").attribute("r").as_float() );
		dataSpheres.at( i ).push_back( tool.child("material_solid").child("transmittance").attribute("t").as_float() );
		dataSpheres.at( i ).push_back( tool.child("material_solid").child("refraction").attribute("iof").as_float() );
		++i;
	}
/*
	for( unsigned int i = 0; i < dataSpheres.size(); ++i ){
		for( unsigned int j = 0; j < dataSpheres.at( i ).size(); ++j ){
			stringstream sstr;
			sstr << dataSpheres.at( i ).at( j );
			cout << sstr.str() << " ";
		}
		cout << endl;
	}
*/
	return dataSpheres;
}

string XMLParser::get_inputFilePath(){
	return inputFilePath;
}
string XMLParser::get_outputFileName(){
	return outputFileName;
}
glm::vec4 XMLParser::get_posCamera(){
	return posCamera;
}
glm::vec4 XMLParser::get_upCamera(){
	return upCamera;
}
glm::vec4 XMLParser::get_lookAtCamera(){
	return lookAtCamera;
}
double XMLParser::get_horizontal_fov(){
	return horizontal_fov;
}
int XMLParser::get_maxBounces(){
	return maxBounces;
}
int XMLParser::get_heightImgPlane(){
	return heightImgPlane;
}
int XMLParser::get_widthImgPlane(){
	return widthImgPlane;
}
glm::vec3 XMLParser::get_bgcolor(){
	return bgcolor;
}
glm::vec3 XMLParser::get_ambientLight(){
	return ambientLight;
}
glm::vec3 XMLParser::get_parallelLightCol(){
	return parallelLightCol;
}
glm::vec3 XMLParser::get_parallelLightDir(){
	return parallelLightDir;
}
std::vector < glm::vec3 > XMLParser::get_pointLightsCol(){
	return pointLightsCol;
}
std::vector < glm::vec3 > XMLParser::get_pointLightsPos(){
	return pointLightsPos;
}

