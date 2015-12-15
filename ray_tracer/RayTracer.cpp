/*
 * RayTracer.cpp
 *
 *  Created on: 12.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include <string>
#include "RayTracer.h"
#include "OutputPPM.h"
#include "OutputImage.h"
#include "Projection.h"
using namespace std;

int main() {
	RayTracer raytracer;
	raytracer.main();
	return 0;
}

void RayTracer::main() {
	cout<<"RayTracer.main()" << endl;

	glm::vec4 posCamera = glm::vec4 ( 0.0, 0.0, 0.0, 1.0 );
	glm::vec4 upCamera = glm::vec4 ( 0, 1, 0, 1 );
	glm::vec4 lookAtCamera = glm::vec4 ( 0, 0, 0, 1 );
	float horizontal_fov = 45;
	float vertical_fov = 45;
	int heightImgPlane = 512;
	int widthImgPlane = 512;

	Projection projection( posCamera, upCamera, lookAtCamera, horizontal_fov, vertical_fov, heightImgPlane, widthImgPlane );
	//projection.print();
	//projection.printContentImgPlane();
	string ppmOutput;
	int width = projection.getWidthImgPlane();
	int height = projection.getHeightImgPlane();
	ppmOutput = projection.contentImgPlaneToString();

	string fileName = "example";
	OutputImage* outputImage = new OutputPPM();
	outputImage->createOutput( fileName, ppmOutput, height, width );


}


