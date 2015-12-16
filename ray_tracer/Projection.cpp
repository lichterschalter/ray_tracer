/*
 * Projection.cpp
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türk
 */



#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "../libs/glm/glm/mat4x4.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/glm/gtx/string_cast.hpp"
#include "Projection.h"
#include "Matrix_vec_math.h"
using namespace std;

Projection::Projection( glm::vec4 posCamera, glm::vec4 upCamera, glm::vec4 lookAtCamera, \
		double horizontal_fov, double vertical_fov, int heightImgPlane, int widthImgPlane ){

	//INIT VARS FROM PARAMETERS
	this->posCamera = posCamera;
	this->upCamera = upCamera;
	this->lookAtCamera = lookAtCamera;
	this->horizontal_fov = horizontal_fov;
	this->vertical_fov = vertical_fov;
	this->heightImgPlane = heightImgPlane;
	this->widthImgPlane = widthImgPlane;

	//COMPUTE TOPLEFT AND BOTTOMRIGHT OF IMGPLANE
	Matrix_vec_math matrixvecmath;
	glm::vec3 posImgPlaneCenter = matrixvecmath.vec4ToVec3(lookAtCamera) - matrixvecmath.vec4ToVec3(posCamera);
	double lengthposImgPlaneCenter = matrixvecmath.lengthVec3( posImgPlaneCenter );
	double lengthImgPlaneCenterToLeft = ( tan ( -horizontal_fov ) ) * lengthposImgPlaneCenter;
	glm::vec3 centerToLeftImgPlane( lengthImgPlaneCenterToLeft, 0.0, 0.0 );
	double lengthImgPlaneCenterToUp = ( ( double(heightImgPlane) / 2)  / ( double(widthImgPlane) / 2 ) ) * lengthImgPlaneCenterToLeft;
	glm::vec3 centerToUpImgPlane( 0.0, lengthImgPlaneCenterToUp, 0.0 );

	//posImgPlaneTopLeft = posImgPlaneCenter + centerToLeftImgPlane + centerToUpImgPlane;
	//posImgPlaneBottomRight = posImgPlaneCenter - centerToLeftImgPlane - centerToUpImgPlane;
	posImgPlaneBottomRight = glm::vec4 ( 0.0, 0.0, 0.0, 1.0 );
	cout << glm::to_string(posImgPlaneTopLeft) << endl;
	cout << glm::to_string(posImgPlaneBottomRight) << endl;
	cout << glm::to_string(posImgPlaneCenter) << endl;
	cout << glm::to_string(centerToLeftImgPlane) << endl;
	cout << lengthImgPlaneCenterToLeft << endl;
	cout << lengthImgPlaneCenterToUp << endl;

	glm::mat4 transMatrix( 1.0f );
	transMatrix = translate( transMatrix, centerToUpImgPlane );
	transMatrix = translate( transMatrix, centerToLeftImgPlane );
	transMatrix = translate( transMatrix, posImgPlaneCenter );
	posImgPlaneTopLeft = transMatrix * posCamera;
	cout << glm::to_string(transMatrix) << endl;
	cout << glm::to_string(posImgPlaneTopLeft) << endl;

	//FILL CONTENT OF IMGPLANE WITH BLACK PIXELS (use contentImgPlane[row][column])
	for (int i = 0; i < heightImgPlane; i++) {
		contentImgPlane.push_back(vector<string>()); // Add one empty row
	}
	for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    for (int j = 0; j < widthImgPlane; j++) {
	    	contentImgPlane.at( i ).push_back( "0 0 0  " ); // Add column to every rows
	    }
	}

};
Projection::~Projection(){ };
Projection::Projection( const Projection& ){
	cerr << "Copy assignment constructor should not be used!" << endl;
	posCamera = glm::vec4 ( 0.0, 0.0, 0.0, 1.0 );
	upCamera = glm::vec4 ( 0.0, 1.0, 0.0, 1.0 );
	lookAtCamera = glm::vec4 ( 0.0, 0.0, 0.0, 1.0 );
	horizontal_fov = 45;
	vertical_fov = 45;
	heightImgPlane = 512;
	widthImgPlane = 512;

	posImgPlaneTopLeft = glm::vec4 ( 0.0, 0.0, 0.0, 1.0 );
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
	for (int j = 0; j < widthImgPlane; j++){
		cout << "    " << j << ":       ";
	}
	cout << endl;
	for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
		cout << i << ": ";
	    for (int j = 0; j < widthImgPlane; j++) {
	    	cout << "| " << contentImgPlane.at( i ).at( j ) << " |  ";
	    }
	    cout << endl;
	}
}

string Projection::contentImgPlaneToString(){
	string outputString;

	for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    for (int j = 0; j < widthImgPlane; j++) {
	    	outputString.append( contentImgPlane.at( i ).at( j ) );
	    }
	    outputString.append("\n");
	}
	return outputString;
}

int Projection::getWidthImgPlane(){
	return widthImgPlane;
}

int Projection::getHeightImgPlane(){
	return heightImgPlane;
}



