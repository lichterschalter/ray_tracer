/*
 * RayTracer.cpp
 *
 *  Created on: 12.12.2015
 *      Author: rustong_pu
 */

#include <iostream>
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

	OutputImage* outputImage = new OutputPPM();
	outputImage->createOutput();
}


