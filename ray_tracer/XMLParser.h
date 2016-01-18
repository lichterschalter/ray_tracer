/*
 * XMLParser.h
 *
 *  Created on: 19.12.2015
 *      Author: Fabian Türk
 */

#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <string>
#include <vector>
#include "../libs/pugixml-1.7/src/pugixml.hpp"

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
	pugi::xml_document doc;
	glm::vec3 ambientLight;
	glm::vec3 parallelLightCol;
	glm::vec3 parallelLightDir;
	std::vector < glm::vec3 > pointLightsCol;
	std::vector < glm::vec3 > pointLightsPos;

	XMLParser( const XMLParser& xmlParser );
	XMLParser& operator=( const XMLParser& xmlParser );
public:
	XMLParser( std::string inputFilePath );
	~XMLParser( );

	std::vector< std::vector<float> > get_dataSpheres( );
	std::string get_inputFilePath();
	std::string get_outputFileName();
	glm::vec4 get_posCamera();
	glm::vec4 get_upCamera();
	glm::vec4 get_lookAtCamera();
	double get_horizontal_fov();
	int get_maxBounces();
	int get_heightImgPlane();
	int get_widthImgPlane();
	glm::vec3 get_bgcolor();
	pugi::xml_document get_doc();
	glm::vec3 get_ambientLight();
	glm::vec3 get_parallelLightCol();
	glm::vec3 get_parallelLightDir();
	std::vector < glm::vec3 > get_pointLightsCol();
	std::vector < glm::vec3 > get_pointLightsPos();

	std::vector< std::vector<float> > dataSpheres( );

	void print( );
};



#endif /* XMLPARSER_H_ */
