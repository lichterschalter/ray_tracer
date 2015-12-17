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
#include "Sphere.h"
#include "Mesh.h"
using namespace std;

int main() {
	RayTracer raytracer;
	raytracer.main();
	return 0;
}

void RayTracer::main() {
	cout<<"RayTracer.main()" << endl;

	glm::vec4 posCamera = glm::vec4 ( 0.0, 0.0, 0.0, 1.0 );
	glm::vec4 upCamera = glm::vec4 ( 0.0, 1.0, 0.0, 1.0 );
	glm::vec4 lookAtCamera = glm::vec4 ( 0.0, 0.0, -2.5, 1.0 );
	double horizontal_fov = 45;
	double vertical_fov = 45;
	int maxBounces = 8;
	int heightImgPlane = 512;
	int widthImgPlane = 512;
	glm::vec3 bgcolor = glm::vec3( 0.0, 0.0, 0.0 );

	Projection projection( posCamera, upCamera, lookAtCamera, horizontal_fov, vertical_fov, maxBounces, heightImgPlane, widthImgPlane, bgcolor );
	projection.print();
	//projection.printContentImgPlane();
	string ppmOutput;
	int width = projection.getWidthImgPlane();
	int height = projection.getHeightImgPlane();
	ppmOutput = projection.contentImgPlaneToString();

	string fileName = "example";
	OutputImage* outputImage = new OutputPPM();
	outputImage->createOutput( fileName, ppmOutput, "512", height, width );

	glm::vec4 posSphere( 0.0, 0.0, 0.0, 1.0 );
	Sphere sphere( posSphere, 1.0 );
	sphere.print();
	cout << width << height << endl;


}


