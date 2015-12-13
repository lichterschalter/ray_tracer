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
		100 \n";
	while( height > 0 ){
		--height;
		int w = width;
		while( w > 0){
			--w;
			myfile << "0 0 0  ";
		}
		myfile << "\n";
	}
	myfile.close();
}

