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

	Projection projection;
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


