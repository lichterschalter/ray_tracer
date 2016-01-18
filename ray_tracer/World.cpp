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
#include <algorithm>
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
		double horizontal_fov, int maxBounces, int heightImgPlane, int widthImgPlane, glm::vec3 bgcolor ){

	cout << "Building the world. ";

	//INIT VARS FROM PARAMETERS
	this->posCamera = posCamera;
	this->upCamera = upCamera;
	this->lookAtCamera = lookAtCamera;
	this->horizontal_fov = horizontal_fov;
	this->heightImgPlane = heightImgPlane;
	this->widthImgPlane = widthImgPlane;
	this->maxBounces = maxBounces;
	this->bgcolor = bgcolor;


	//COMPUTE TOPLEFT AND BOTTOMRIGHT OF IMGPLANE

	//1. calculate points and vectors to reach topleft and bottomright from poscamera
	Matrix_vec_math matrixvecmath;

	glm::vec4 dir( lookAtCamera[ 0 ] - posCamera[ 0 ], lookAtCamera[ 1 ] - posCamera[ 1 ], lookAtCamera[ 2 ] - posCamera[ 2 ], 1.0 );
	dir = matrixvecmath.normalize( dir );
	upCamera = matrixvecmath.normalize( upCamera );
	rightVec = matrixvecmath.crossVec4( dir, upCamera );
	upCamera = matrixvecmath.crossVec4( rightVec, dir );

	double pi = 3.1415926535897;
	float width = 2 * ( tan (horizontal_fov * pi / 180.0 ) * matrixvecmath.lengthVec4( dir ) );
	float height = width / ( widthImgPlane / heightImgPlane );

	glm::vec3 halfWidthVec( width / 2, 0, 0 );
	glm::vec3 halfHeightVec( 0, height / 2, 0 );
	glm::vec3 lookAtTemp = matrixvecmath.vec4ToVec3( lookAtCamera );
	glm::vec3 rightVecTemp = matrixvecmath.vec4ToVec3( rightVec );
	glm::vec3 upCameraTemp = matrixvecmath.vec4ToVec3( upCamera );

	pixelWidth = ( width / widthImgPlane );
	pixelHeight = ( height / heightImgPlane );

	glm::vec3 topLeftTemp = lookAtTemp + ( halfWidthVec * ( -rightVecTemp ) ) + ( halfHeightVec * ( upCameraTemp ) );
	posImgPlaneTopLeft = matrixvecmath.vec3ToVec4( topLeftTemp );


	//FILL CONTENT OF IMGPLANE WITH BLACK PIXELS (use contentImgPlane[row][column])
	for (int i = 0; i < heightImgPlane; i++) {
		contentImgPlane.push_back(vector<string>()); // Add one empty row
	}
	for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    for (int j = 0; j < widthImgPlane; j++) {
	    	contentImgPlane.at( i ).push_back( "0 0 0  " ); // Add column to every rows
	    }
	}

	cout << "World creation was successfull." << endl;

};
World::~World(){ };
World::World( const World& world){
	cerr << "WARNING: Copy constructor should not be used!" << endl;

	//INIT VARS FROM PARAMETERS
	this->spheres = world.spheres;
	this->posCamera = world.posCamera;
	this->upCamera = world.upCamera;
	this->lookAtCamera = world.lookAtCamera;
	this->horizontal_fov = world.horizontal_fov;
	this->heightImgPlane = world.heightImgPlane;
	this->widthImgPlane = world.widthImgPlane;
	this->posImgPlaneTopLeft = world.posImgPlaneTopLeft;
	this->maxBounces = world.maxBounces;
	this->bgcolor = world.bgcolor;
	this->pixelWidth = world.pixelWidth;
	this->pixelHeight = world.pixelHeight;

};
World& World::operator=( const World& ){
	cerr << "WARNING: Copy assignment operator should not be used!" << endl;
	return *this;
};

void World::createSphere( Sphere sphere ){
	spheres.push_back( sphere );
}
void World::createMesh( Mesh mesh ){
	;
}

void World::print(){
	cout << endl;
	cout << "----begin class World----" << endl;
	cout << "posCamera: " << glm::to_string(posCamera) << endl;
	cout << "upCamera: " << glm::to_string(upCamera) << endl;
	cout << "lookAtCamera: " << glm::to_string(lookAtCamera) << endl;
	cout << "horizontal_fov: " << horizontal_fov << endl;
	cout << "maxBounces: " << maxBounces << endl;
	cout << "posImgPlaneTopLeft: " << glm::to_string(posImgPlaneTopLeft) << endl;
	cout << "heightImgPlane: " << heightImgPlane << endl;
	cout << "contentImgPlane: [is not printed, use printContentImgPlane() to print it]" << endl;
	cout << "ray: \n [ " << ray.toString() << " ]"<< endl;
	cout << "bgcolor: " << glm::to_string(bgcolor) << endl;

	for( unsigned int i = 0; i < spheres.size(); ++i ){
		spheres.at( i ).print();
	}

	cout << "----end class World----" << endl << endl;
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

void World::performRayTracing(){
	Matrix_vec_math matrixvecmath;
	cout << "Shooting rays into the world..." << endl;


	//TEST SPHERE FOR DEBUGGING

	//glm::vec3 posSphere( -2.1, 0.0, -7.0 );
	//float radiusSphere = 7.5;


	//SHOOT RAYS TO THE CENTER OF EVERY PIXEL ON THE IMAGE PLANE

	glm::vec3 posRayOnPlane = matrixvecmath.vec4ToVec3( posImgPlaneTopLeft ) - matrixvecmath.vec4ToVec3( posCamera );
	posRayOnPlane[ 0 ] += pixelWidth / 2;
	posRayOnPlane[ 1 ] -= pixelHeight / 2;
	cout << glm::to_string(posImgPlaneTopLeft) << endl;
	cout << glm::to_string(posRayOnPlane) << endl;

	this->ray = Ray( glm::vec4( posRayOnPlane[ 0 ], posRayOnPlane[ 1 ], posRayOnPlane[ 2 ], 1.0 ) );

	contentImgPlane.clear();
	for (int i = 0; i < heightImgPlane; i++) {
		contentImgPlane.push_back(vector<string>()); // Add one empty row
	}
	for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    for (int j = 0; j < widthImgPlane; j++) {
			Ray ray( glm::vec4( posRayOnPlane[ 0 ] + j, posRayOnPlane[ 1 ] - i, posRayOnPlane[ 2 ], 1.0 ) );
			//ray.normalize();

			//1. perform intersection test ray-sphere
			vector< float > intersections;
			for( unsigned int i = 0; i < spheres.size(); ++i ){
				glm::vec4 posSphere( spheres.at( i ).get_position() );
				float radiusSphere = spheres.at( i ).get_radius();
				float a =  ray.getX() * ray.getX() +
						   ray.getY() * ray.getY() +
						   ray.getZ() * ray.getZ();

				float b =  pow ( ( 2 * posCamera[ 0 ] * ray.getX() - 2 * posSphere[ 0 ] * ray.getX() ), 2 ) +
						   pow ( ( 2 * posCamera[ 1 ] * ray.getY() - 2 * posSphere[ 1 ] * ray.getY() ), 2 ) +
						   pow ( ( 2 * posCamera[ 2 ] * ray.getZ() - 2 * posSphere[ 2 ] * ray.getZ() ), 2 );

				float c = pow ( posCamera[ 0 ] - posSphere[ 0 ], 2 ) +
						  pow ( posCamera[ 1 ] - posSphere[ 1 ], 2 ) +
						  pow ( posCamera[ 2 ] - posSphere[ 2 ], 2 ) -
						  pow ( radiusSphere, 2 );
				float intersection = b - 4 * a * c;
				intersections.push_back( intersection );
			}

			//2. find biggest delta
			int indexBiggest = 0;
			for( unsigned int i = 0; i < intersections.size(); ++i ){
				float* biggest = &intersections.at( i );
				for( unsigned int j = 1; j < intersections.size() - i; ++j ){
					float* smaller = &intersections.at( i + j );
					if( *biggest < *smaller ){
						indexBiggest = j;
						float temp = *smaller;
						*smaller = *biggest;
						*biggest = temp;
					}
				}
			}

			//3. find color of intersection
			float intersection = intersections.at( indexBiggest );
			glm::vec3 colorIntersection = spheres.at( indexBiggest ).get_color();
			stringstream sstr;
			sstr << int ( colorIntersection[ 0 ] * widthImgPlane ) << " " << int ( colorIntersection[ 1 ] * widthImgPlane ) << " " << int ( colorIntersection[ 2 ] * widthImgPlane ) << "    ";
			string colorPixel = sstr.str();

			//4. save color to imgPlane
	    	if( intersection >= 0 ) {
		    	contentImgPlane.at( i ).push_back( colorPixel );
	    	}else{
		    	//contentImgPlane.at( i ).push_back( "0 0 0   " );
	    		contentImgPlane.at( i ).push_back( ray.posToColorString() + "  " );
	    	}

	    }
    	contentImgPlane.at( i ).push_back( "\n" ); // Add column to every row
	}

	cout << "Ray tracing was successfull!" << endl;
}


