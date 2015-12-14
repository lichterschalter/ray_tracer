/*
 * OutputPPM.cpp
 *
 *  Created on: 13.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include <fstream>
#include <string>
#include "OutputPPM.h"
#include "OutputImage.h"
using namespace std;

OutputPPM::OutputPPM(){ };
OutputPPM::~OutputPPM(){ };
OutputPPM::OutputPPM( const OutputPPM& ){ };
OutputPPM& OutputPPM::operator=( const OutputPPM& ){ return *this; };



void OutputPPM::createOutput( string fileName, string content, int width, int height ){
	cout << "OutputPPM.createOutput()"<<endl;
	string fName = fileName + ".ppm";
	const char * fNameConst = fName.c_str();
	ofstream myfile;
	myfile.exceptions ( std::ofstream::failbit | std::ofstream::badbit );
	try{
		myfile.open(fNameConst);
		myfile << "P3 \n \
			# sample.ppm \n" << \
			width << " " << height << " \n \
			100 \n";
		myfile << content;
		/*
		while( height > 0 ){
			--height;
			int w = width;
			while( w > 0){
				--w;
				myfile << "0 0 0  ";
			}
			myfile << "\n";
		}*/
	}catch( exception const &e ){
		cerr << "Exception writing PPM file!" << endl;
	}
	myfile.close();
}

