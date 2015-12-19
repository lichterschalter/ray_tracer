/*
 * RayTracer.cpp
 *
 *  Created on: 12.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include <string>
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
	cout << "RayTracer is activated!" << endl;
	cout << "This RayTracer was created by Fabian Türk." << endl;


	//PARSING THE INPUT FROM XML FILE
	//string inputFileName = "";
	//cout << "Type in the name of the input file (f.e.: 'example1.xml' ): ";
	//cin >> inputFileName;
	string inputFileName = "example1.xml";

	XMLParser xmlParser( "../scenes/" + inputFileName );
	xmlParser.print();
	xmlParser.dataSpheres();

	string outputFileName = "example";
	glm::vec4 posCamera = glm::vec4 ( -1.0, 1.0, 0.188, 1.0 );
	glm::vec4 upCamera = glm::vec4 ( 0.0, 1.0, 0.0, 1.0 );
	glm::vec4 lookAtCamera = glm::vec4 ( 0.0, 0.0, -2.5, 1.0 );
	double horizontal_fov = 45;
	double vertical_fov = 45;
	int maxBounces = 8;
	int heightImgPlane = 512;
	int widthImgPlane = 512;
	glm::vec3 bgcolor = glm::vec3( 0.0, 0.0, 0.0 );


	//CREATING THE WORLD
	World world( posCamera, upCamera, lookAtCamera, horizontal_fov, vertical_fov, maxBounces, heightImgPlane, widthImgPlane, bgcolor );
	//world.print();
	//world.printContentImgPlane();


	//CREATE OUTPUT
	string ppmOutput;
	int width = world.getWidthImgPlane();
	int height = world.getHeightImgPlane();
	ppmOutput = world.contentImgPlaneToString();
	OutputImage* outputImage = new OutputPPM();
	outputImage->createOutput( outputFileName, ppmOutput, "512", height, width );


	//OTHER STUFF
	glm::vec4 posSphere( 0.0, 0.0, 0.0, 1.0 );
	Sphere sphere( posSphere, 1.0 );
	//sphere.print();
	cout << width << height << endl;


}


