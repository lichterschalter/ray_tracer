/*
 * World.cpp
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türk
 */



#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "../libs/glm/glm/mat4x4.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/glm/gtx/string_cast.hpp"
#include "Matrix_vec_math.h"
#include "World.h"
#include "Sphere.h"
#include "Mesh.h"
using namespace std;

World::World( glm::vec4 posCamera, glm::vec4 upCamera, glm::vec4 lookAtCamera, \
		double horizontal_fov, double vertical_fov, int maxBounces, int heightImgPlane, int widthImgPlane, glm::vec3 bgcolor ){


	//INIT VARS FROM PARAMETERS
	this->spheres = 0;
	this->posCamera = posCamera;
	this->upCamera = upCamera;
	this->lookAtCamera = lookAtCamera;
	this->horizontal_fov = horizontal_fov;
	this->vertical_fov = vertical_fov;
	this->heightImgPlane = heightImgPlane;
	this->widthImgPlane = widthImgPlane;
	this->maxBounces = maxBounces;
	this->bgcolor = bgcolor;


	//COMPUTE TOPLEFT AND BOTTOMRIGHT OF IMGPLANE

	//1. calculate points and vectors to reach topleft and bottomright from poscamera
	Matrix_vec_math matrixvecmath;
	glm::vec3 posImgPlaneCenter = matrixvecmath.vec4ToVec3(lookAtCamera) - matrixvecmath.vec4ToVec3(posCamera);
	double lengthposImgPlaneCenter = matrixvecmath.lengthVec3( posImgPlaneCenter );
	double lengthImgPlaneCenterToLeft = ( tan ( -horizontal_fov ) ) * lengthposImgPlaneCenter;
	glm::vec3 centerToLeftImgPlane( lengthImgPlaneCenterToLeft, 0.0, 0.0 );
	double lengthImgPlaneCenterToTop = ( ( double(heightImgPlane) / 2)  / ( double(widthImgPlane) / 2 ) ) * -lengthImgPlaneCenterToLeft;
	glm::vec3 centerToUpImgPlane( 0.0, lengthImgPlaneCenterToTop, 0.0 );
	double lengthImgPlaneCenterToRight = ( tan ( horizontal_fov ) ) * lengthposImgPlaneCenter;
	glm::vec3 centerToRightImgPlane( lengthImgPlaneCenterToRight, 0.0, 0.0 );
	double lengthImgPlaneCenterToBottom = ( ( double(heightImgPlane) / 2)  / ( double(widthImgPlane) / 2 ) ) * -lengthImgPlaneCenterToRight;
	glm::vec3 centerToBottomImgPlane( 0.0, lengthImgPlaneCenterToBottom, 0.0 );

	//2a. matrix multiplications for topleft
	glm::mat4 transMatrix( 1.0f );
	transMatrix = translate( transMatrix, centerToUpImgPlane );
	transMatrix = translate( transMatrix, centerToLeftImgPlane );
	transMatrix = translate( transMatrix, posImgPlaneCenter );
	posImgPlaneTopLeft = transMatrix * posCamera;

	//2b. matrix mulitplication for bottom right
	transMatrix = glm::mat4( 1.0f );
	transMatrix = translate( transMatrix, centerToBottomImgPlane );
	transMatrix = translate( transMatrix, centerToRightImgPlane );
	transMatrix = translate( transMatrix, posImgPlaneCenter );
	posImgPlaneBottomRight = transMatrix * posCamera;


	//COMPUTE INTERSECTIONS WITH SPHERES
	Ray rayIntersect( glm::vec4( 1.0, 1.0, -5.0, 1.0 ) );
	rayIntersect.normalize();
	//pow ( (2 * posCamera * rayIntersect - 2 * posCamera * posSphere * rayIntersect), 2 ) - 4 * pow( rayIntersect, 2) * ( posCamera - posSphere ) - radius;


	//SHOOT RAYS TO THE CENTER OF EVERY PIXEL ON THE IMAGE PLANE

	double pixelWidth = ( 2 * lengthImgPlaneCenterToRight ) / this->widthImgPlane;
	double pixelHeight = ( 2 * lengthImgPlaneCenterToTop ) / this->widthImgPlane;
	glm::vec3 posRayOnPlane = matrixvecmath.vec4ToVec3( posImgPlaneTopLeft ) - matrixvecmath.vec4ToVec3( posCamera );
	posRayOnPlane[ 0 ] += pixelWidth;
	posRayOnPlane[ 1 ] -= pixelHeight;
	cout << glm::to_string(posRayOnPlane) << endl;

	Ray ray( glm::vec4( posRayOnPlane[ 0 ], posRayOnPlane[ 1 ], posRayOnPlane[ 2 ], 1.0 ) );
	this->ray = ray;

	for (int i = 0; i < heightImgPlane; i++) {
		contentImgPlane.push_back(vector<string>()); // Add one empty row
	}
	for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    for (int j = 0; j < widthImgPlane; j++) {
			Ray ray( glm::vec4( posRayOnPlane[ 0 ] + j, posRayOnPlane[ 1 ] - i, posRayOnPlane[ 2 ], 1.0 ) );
	    	contentImgPlane.at( i ).push_back( ray.posToColorString() + "  " ); // Add column to every rows
	    }
    	contentImgPlane.at( i ).push_back( "\n" ); // Add column to every rows
	}

/*
	//FILL CONTENT OF IMGPLANE WITH BLACK PIXELS (use contentImgPlane[row][column])
	for (int i = 0; i < heightImgPlane; i++) {
		contentImgPlane.push_back(vector<string>()); // Add one empty row
	}
	for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    for (int j = 0; j < widthImgPlane; j++) {
	    	contentImgPlane.at( i ).push_back( "0 0 0  " ); // Add column to every rows
	    }
	}
	*/

};
World::~World(){ };
World::World( const World& world){
	cerr << "Copy assignment constructor should not be used!" << endl;

	//INIT VARS FROM PARAMETERS
	this->spheres = world.spheres;
	this->posCamera = world.posCamera;
	this->upCamera = world.upCamera;
	this->lookAtCamera = world.lookAtCamera;
	this->horizontal_fov = world.horizontal_fov;
	this->vertical_fov = world.vertical_fov;
	this->heightImgPlane = world.heightImgPlane;
	this->widthImgPlane = world.widthImgPlane;
	this->maxBounces = world.maxBounces;
	this->bgcolor = world.bgcolor;


	//COMPUTE TOPLEFT AND BOTTOMRIGHT OF IMGPLANE

	//1. calculate points and vectors to reach topleft and bottomright from poscamera
	Matrix_vec_math matrixvecmath;
	glm::vec3 posImgPlaneCenter = matrixvecmath.vec4ToVec3(lookAtCamera) - matrixvecmath.vec4ToVec3(posCamera);
	double lengthposImgPlaneCenter = matrixvecmath.lengthVec3( posImgPlaneCenter );
	double lengthImgPlaneCenterToLeft = ( tan ( -horizontal_fov ) ) * lengthposImgPlaneCenter;
	glm::vec3 centerToLeftImgPlane( lengthImgPlaneCenterToLeft, 0.0, 0.0 );
	double lengthImgPlaneCenterToTop = ( ( double(heightImgPlane) / 2)  / ( double(widthImgPlane) / 2 ) ) * -lengthImgPlaneCenterToLeft;
	glm::vec3 centerToUpImgPlane( 0.0, lengthImgPlaneCenterToTop, 0.0 );
	double lengthImgPlaneCenterToRight = ( tan ( horizontal_fov ) ) * lengthposImgPlaneCenter;
	glm::vec3 centerToRightImgPlane( lengthImgPlaneCenterToRight, 0.0, 0.0 );
	double lengthImgPlaneCenterToBottom = ( ( double(heightImgPlane) / 2)  / ( double(widthImgPlane) / 2 ) ) * -lengthImgPlaneCenterToRight;
	glm::vec3 centerToBottomImgPlane( 0.0, lengthImgPlaneCenterToBottom, 0.0 );

	//2a. matrix multiplications for topleft
	glm::mat4 transMatrix( 1.0f );
	transMatrix = translate( transMatrix, centerToUpImgPlane );
	transMatrix = translate( transMatrix, centerToLeftImgPlane );
	transMatrix = translate( transMatrix, posImgPlaneCenter );
	posImgPlaneTopLeft = transMatrix * posCamera;

	//2b. matrix mulitplication for bottom right
	transMatrix = glm::mat4( 1.0f );
	transMatrix = translate( transMatrix, centerToBottomImgPlane );
	transMatrix = translate( transMatrix, centerToRightImgPlane );
	transMatrix = translate( transMatrix, posImgPlaneCenter );
	posImgPlaneBottomRight = transMatrix * posCamera;


	//SHOOT RAYS TO THE CENTER OF EVERY PIXEL ON THE IMAGE PLANE
	Ray ray( glm::vec4( 0.0, 0.0, 0.0, 1.0 ) );
	this->ray = ray;


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
World& World::operator=( const World& ){ return *this; };

void World::createSphere( Sphere sphere ){
	;
}
void World::createMesh( Mesh mesh ){
	;
}

void World::print(){
	cout << endl;
	cout << "--begin class World--" << endl;
	cout << "posCamera: " << glm::to_string(posCamera) << endl;
	cout << "upCamera: " << glm::to_string(upCamera) << endl;
	cout << "lookAtCamera: " << glm::to_string(lookAtCamera) << endl;
	cout << "horizontal_fov: " << horizontal_fov << endl;
	cout << "vertical_fov: " << vertical_fov << endl;
	cout << "maxBounces: " << maxBounces << endl;
	cout << "posImgPlaneTopLeft: " << glm::to_string(posImgPlaneTopLeft) << endl;
	cout << "posImgPlaneBottomRight: " << glm::to_string(posImgPlaneBottomRight) << endl;
	cout << "heightImgPlane: " << heightImgPlane << endl;
	cout << "contentImgPlane: [is not printed, use printContentImgPlane() to print it]" << endl;
	cout << "ray: \n [ " << ray.toString() << " ]"<< endl;
	cout << "bgcolor: " << glm::to_string(bgcolor) << endl;
	cout << "--end class World--" << endl << endl;
}

void World::printContentImgPlane(){
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

string World::contentImgPlaneToString(){
	string outputString;

	for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    for (int j = 0; j < widthImgPlane; j++) {
	    	outputString.append( contentImgPlane.at( i ).at( j ) );
	    }
	    outputString.append("\n");
	}
	return outputString;
}

int World::getWidthImgPlane(){
	return widthImgPlane;
}

int World::getHeightImgPlane(){
	return heightImgPlane;
}


