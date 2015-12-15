/*
 * Projection.cpp
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türk
 */



#include <iostream>
#include <vector>
#include <string>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "../libs/glm/glm/gtx/string_cast.hpp"
#include "Projection.h"
using namespace std;

Projection::Projection( glm::vec4 posCamera, glm::vec4 upCamera, glm::vec4 lookAtCamera, \
		float horizontal_fov, float vertical_fov, int heightImgPlane, int widthImgPlane ){
	this->posCamera = posCamera;
	this->upCamera = upCamera;
	this->lookAtCamera = lookAtCamera;
	this->horizontal_fov = horizontal_fov;
	this->vertical_fov = vertical_fov;
	this->heightImgPlane = heightImgPlane;
	this->widthImgPlane = widthImgPlane;

	posImgPlaneTopLeft = glm::vec4 ( 0, 0, 0, 1 );
	posImgPlaneBottomRight = glm::vec4 ( 0, 0, 0, 1 );

	//use contentImgPlane[row][column]
	for (int i = 0; i < widthImgPlane; i++) {
		contentImgPlane.push_back(vector<string>()); // Add one empty row
	}
	for (int j = 0; j < heightImgPlane; j++) {
	    for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    	contentImgPlane.at( i ).push_back( "0 0 0  " ); // Add column to every rows
	    }
	}
};
Projection::~Projection(){ };
Projection::Projection( const Projection& ){
	posCamera = glm::vec4 ( 0.0, 0.0, 0.0, 1.0 );
	upCamera = glm::vec4 ( 0, 1, 0, 1 );
	lookAtCamera = glm::vec4 ( 0, 0, 0, 1 );
	horizontal_fov = 45;
	vertical_fov = 45;
	posImgPlaneTopLeft = glm::vec4 ( 0, 0, 0, 1 );
	posImgPlaneBottomRight = glm::vec4 ( 0, 0, 0, 1 );
	heightImgPlane = 512;
	widthImgPlane = 10;

	//use contentImgPlane[row][column]
	for (int i = 0; i < widthImgPlane; i++) {
		contentImgPlane.push_back(vector<string>()); // Add one empty row
	}
	for (int j = 0; j < heightImgPlane; j++) {
	    for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    	contentImgPlane.at( i ).push_back( "0 0 0  " ); // Add column to every rows
	    }
	}
};
Projection& Projection::operator=( const Projection& ){ return *this; };

void Projection::print(){
	cout << endl;
	cout << "--begin class Projection--" << endl;
	cout << "posCamera: " << glm::to_string(posCamera) << endl;
	cout << "upCamera: " << glm::to_string(upCamera) << endl;
	cout << "lookAtCamera: " << glm::to_string(lookAtCamera) << endl;
	cout << "horizontal_fov: " << horizontal_fov << endl;
	cout << "vertical_fov: " << vertical_fov << endl;
	cout << "posImgPlaneTopLeft: " << glm::to_string(posImgPlaneTopLeft) << endl;
	cout << "posImgPlaneBottomRight: " << glm::to_string(posImgPlaneBottomRight) << endl;
	cout << "heightImgPlane: " << heightImgPlane << endl;
	cout << "contentImgPlane: [is not printed, use printContentImgPlane() to print it]" << endl;
	cout << "ray: \n [ " << ray.toString() << " ]"<< endl;
	cout << "--end class Projection--" << endl << endl;
}

void Projection::printContentImgPlane(){
	for (unsigned int i = 0; i < contentImgPlane.size(); i++){
		cout << "    " << i << ":       ";
	}
	cout << endl;
	for (int j = 0; j < heightImgPlane; j++) {
		cout << j << ": ";
	    for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    	cout << "| " << contentImgPlane.at( i ).at( j ) << " |  ";
	    }
	    cout << endl;
	}
}

string Projection::contentImgPlaneToString(){
	string outputString;
	for (int j = 0; j < widthImgPlane; j++) {
	    for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    	outputString.append( contentImgPlane.at( i ).at( j ) );
	    }
	    outputString.append("\n");
	}
    cout << outputString;
	return outputString;
}

int Projection::getWidthImgPlane(){
	return widthImgPlane;
}

int Projection::getHeightImgPlane(){
	return heightImgPlane;
}



