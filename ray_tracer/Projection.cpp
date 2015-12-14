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

Projection::Projection(){
	posCamera = glm::vec4 ( 0.0, 0.0, 0.0, 0.0 );
	upCamera = glm::vec4 ( 0, 1, 0, 0 );
	horizontal_fov = 45;
	vertical_fov = 45;
	posImgPlaneCenter = glm::vec4 ( 0, 0, 0, 0);
	posImgPlaneTopLeft = glm::vec4 ( 0, 0, 0, 0);
	posImgPlaneBottomRight = glm::vec4 ( 0, 0, 0, 0);
	heightImgPlane = 0;
	widthImgPlane = 0;

	//use contentImgPlane[row][colum]
	int size = 10; //here should be used width later
	for (int i = 0; i < size; i++) {
		contentImgPlane.push_back(vector<int>()); // Add one empty row
	}
	for (int j = 0; j < 20; j++) {
	    for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    	contentImgPlane[i].push_back(i + j); // Add column to every rows
	    }
	}
};
Projection::~Projection(){ };
Projection::Projection( const Projection& ){
	posCamera = glm::vec4 ( 0, 0, 0, 0 );
	upCamera = glm::vec4 ( 0, 1, 0, 0 );
	horizontal_fov = 45;
	vertical_fov = 45;
	posImgPlaneCenter = glm::vec4 ( 0, 0, 0, 0);
	posImgPlaneTopLeft = glm::vec4 ( 0, 0, 0, 0);
	posImgPlaneBottomRight = glm::vec4 ( 0, 0, 0, 0);
	heightImgPlane = 0;
	widthImgPlane = 0;
	//contentImgPlane;
};
Projection& Projection::operator=( const Projection& ){ return *this; };

void Projection::print(){
	cout << endl;
	cout << "--begin class Projection--" << endl;
	cout << "posCamera: " << glm::to_string(posCamera) << endl;
	cout << "upCamera: " << glm::to_string(upCamera) << endl;
	cout << "horizontal_fov: " << horizontal_fov << endl;
	cout << "vertical_fov: " << vertical_fov << endl;
	cout << "posImgPlaneCenter: " << glm::to_string(posImgPlaneCenter) << endl;
	cout << "posImgPlaneTopLeft: " << glm::to_string(posImgPlaneTopLeft) << endl;
	cout << "posImgPlaneBottomRight: " << glm::to_string(posImgPlaneBottomRight) << endl;
	cout << "heightImgPlane: " << heightImgPlane << endl;
	cout << "contentImgPlane: [is not printed, use printContentImgPlane() to print it]" << endl;
	cout << "ray: \n [ " << ray.toString() << " ]"<< endl;
	cout << "--end class Projection--" << endl << endl;
}

void Projection::printContentImgPlane(){
	for (int j = 0; j < 20; j++) {
		cout << j << ": ";
	    for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    	cout << contentImgPlane[ i ][ j ] << ", ";
	    }
	    cout << endl;
	}
}



