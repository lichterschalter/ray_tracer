/*
 * RayTracer.cpp
 *
 *  Created on: 12.12.2015
 *      Author: rustong_pu
 */

#include <iostream>
#include <fstream>
#include "RayTracer.h"
using namespace std;

int main() {
	ofstream myfile;
	myfile.open("example.ppm");
	myfile << "P3 \n \
		# sample.ppm \n \
		4 4 \n \
		15 \n \
		 0  0  0    0  0  0    0  0  0   15  0 15 \n \
		 0  0  0    0 15  7    0  0  0    0  0  0 \n \
		 0  0  0    0  0  0    0 15  7    0  0  0 \n \
		15  0 15    0  0  0    0  0  0    0  0  0";
}


