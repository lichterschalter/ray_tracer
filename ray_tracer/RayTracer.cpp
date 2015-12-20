/*
 * RayTracer.cpp
 *
 *  Created on: 12.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "../libs/glm/glm/mat4x4.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/glm/gtx/string_cast.hpp"
#include "RayTracer.h"
#include "OutputPPM.h"
#include "OutputImage.h"
#include "Sphere.h"
#include "Mesh.h"
#include "World.h"
#include "XMLParser.h"

using namespace std;

int main() {
	RayTracer raytracer;
	raytracer.main();
	return 0;
}

void RayTracer::main() {

	//USER INTERFACE
	cout << "RayTracer is activated!" << endl;
	cout << "This RayTracer was created by Fabian Türk." << endl;
	//string inputFileName = "";
	//cout << "Type in the name of the input file (f.e.: 'example1.xml' ): ";
	//cin >> inputFileName;
	string inputFileName = "example1.xml";


	//PARSING GENERAL INPUT FROM XML FILE
	XMLParser xmlParser( "../scenes/" + inputFileName );
	//xmlParser.print();

	string outputFileName = xmlParser.get_outputFileName();
	glm::vec4 posCamera = xmlParser.get_posCamera();
	glm::vec4 upCamera = xmlParser.get_upCamera();
	glm::vec4 lookAtCamera = xmlParser.get_lookAtCamera();
	double horizontal_fov = xmlParser.get_horizontal_fov();
	int maxBounces = xmlParser.get_maxBounces();
	int heightImgPlane = xmlParser.get_heightImgPlane();
	int widthImgPlane = xmlParser.get_widthImgPlane();
	glm::vec3 bgcolor = xmlParser.get_bgcolor();


	//CREATING THE WORLD
	World world( posCamera, upCamera, lookAtCamera, horizontal_fov, maxBounces, heightImgPlane, widthImgPlane, bgcolor );
	//world.print();
	//world.printContentImgPlane();


	//CREATING OBJECTS FOR THE WOLRD
	vector< vector<float> > dataSpheres = xmlParser.dataSpheres();
	for( unsigned int i = 0; i < dataSpheres.size(); ++i ){
		float radius = dataSpheres.at( i ).at( 0 );
		glm::vec4 position( dataSpheres.at( i ).at( 1 ), dataSpheres.at( i ).at( 2 ), dataSpheres.at( i ).at( 3 ), 1.0 );
		glm::vec3 color( dataSpheres.at( i ).at( 4 ), dataSpheres.at( i ).at( 5 ), dataSpheres.at( i ).at( 6 ) );
		glm::vec4 phong( dataSpheres.at( i ).at( 7 ), dataSpheres.at( i ).at( 8 ), dataSpheres.at( i ).at( 9 ), dataSpheres.at( i ).at( 10 ) );
		float reflectance = dataSpheres.at( i ).at( 11 );
		float transmittance = dataSpheres.at( i ).at( 12 );
		float refraction = dataSpheres.at( i ).at( 13 );
		const Sphere tempSphere( position, color, phong, reflectance, transmittance, refraction, radius );
		world.createSphere( tempSphere );
	}
	//world.print();

	//CREATE OUTPUT
	string ppmOutput;
	int width = world.getWidthImgPlane();
	int height = world.getHeightImgPlane();
	ppmOutput = world.contentImgPlaneToString();
	OutputImage* outputImage = new OutputPPM();
	outputImage->createOutput( outputFileName, ppmOutput, "512", height, width );


	//OTHER STUFF
	//glm::vec4 posSphere( 0.0, 0.0, 0.0, 1.0 );
	//Sphere sphere( posSphere, 1.0 );
	//sphere.print();

}


