/*
 * OutputPPM.cpp
 *
 *  Created on: 13.12.2015
 *      Author: rustong_pu
 */

#include <iostream>
#include <fstream>
#include "OutputPPM.h"
#include "OutputImage.h"
using namespace std;

OutputPPM::~OutputPPM(){ }

void OutputPPM::createOutput( int width, int height ){
	cout << "OutputPPM.createOutput()"<<endl;
	ofstream myfile;
	myfile.open("example.ppm");
	myfile << "P3 \n \
		# sample.ppm \n" << \
		width << " " << height << " \n \
		15 \n \
		 0  0  0    0  0  0    0  0  0   15  0 15 \n \
		 0  0  0   15 15 15    0  0  0    0  0  0 \n \
		 0  0  0    0  0  0    0 15  7    0  0  0 \n \
		15  0 15    0  0  0    0  0  0    0  0  0";
	myfile.close();
}

