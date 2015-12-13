/*
 * RayTracer.cpp
 *
 *  Created on: 12.12.2015
 *      Author: rustong_pu
 */

#include <iostream>
#include <string>
#include "RayTracer.h"
#include "OutputPPM.h"
#include "OutputImage.h"
using namespace std;

int main() {
	RayTracer raytracer;
	raytracer.main();
	return 0;
}

void RayTracer::main() {
	cout<<"RayTracer.main()"<<endl;

	string fileName = "example";
	OutputImage* outputImage = new OutputPPM();
	outputImage->createOutput( fileName, 100, 100 );
}


