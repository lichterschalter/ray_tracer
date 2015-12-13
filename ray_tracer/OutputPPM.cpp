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
	myfile.exceptions ( std::ofstream::failbit | std::ofstream::badbit );
	try{
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
	}catch( ofstream::failure &e ){
		cout << "Exception writing PPM file!";
	}
	myfile.close();
}

