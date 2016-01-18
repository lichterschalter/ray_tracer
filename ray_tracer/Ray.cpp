/*
 * Ray.cpp
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "../libs/glm/glm/gtx/string_cast.hpp"
#include "Ray.h"
using namespace std;

Ray::Ray(  ){
	this->direction = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
	this->length = 0;
};
Ray::Ray( glm::vec4 direction ){
	this->direction = direction;
	this->length = sqrt( pow( direction[ 0 ], 2 ) + pow( direction[ 1 ], 2 ) + pow( direction[ 2 ], 2 ) );
};
Ray::~Ray(){ };
Ray::Ray( const Ray& ray ){
	this->direction = ray.direction;
	this->length = ray.length;
};
Ray& Ray::operator=( const Ray& ray ){
	this->direction = ray.direction;
	this->length = ray.length;
	return *this;
};

string Ray::toString(){
	string directionStr = glm::to_string(direction);
	stringstream sstr;
	sstr << length;
	string lengthStr = sstr.str();
	return "direction: " + directionStr + "\n   length: " + lengthStr;
}

string Ray::posToColorString(){
	/*
	stringstream sstrX, sstrY, sstrZ;
	unsigned int x, y, z;
	x = direction[ 0 ] >= 0 ? direction[ 0 ] : 0;
	y = direction[ 1 ] >= 0 ? direction[ 1 ] : 0;
	z = direction[ 2 ] >= 0 ? direction[ 2 ] : 0;
	sstrX << int(x);
	string posX = sstrX.str();
	sstrY << int(y);
	string posY = sstrY.str();
	sstrZ << int(z);
	string posZ = sstrZ.str();
	return posX + " " + posY + " " + posZ;
	*/

	stringstream sstrX, sstrY, sstrZ;
	unsigned int x, y, z;
	x = direction[ 0 ] * 512;
	y = direction[ 1 ] * 512;
	z = direction[ 2 ] >= 0 ? direction[ 2 ] : 0;
	sstrX << abs(int(x));
	string posX = sstrX.str();
	sstrY << abs(int(y));
	string posY = sstrY.str();
	sstrZ << abs(int(z));
	string posZ = sstrZ.str();
	return posX + " " + posY + " " + posZ;
}

void Ray::normalize(){
		direction[ 0 ] = direction[ 0 ] / length;
		direction[ 1 ] = direction[ 1 ] / length;
		direction[ 2 ] = direction[ 2 ] / length;
		length = sqrt( pow( direction[ 0 ], 2 ) + pow( direction[ 1 ], 2 ) + pow( direction[ 2 ], 2 ) );
}

float Ray::getX(){
	return direction[ 0 ];
}

float Ray::getY(){
	return direction[ 1 ];
}

float Ray::getZ(){
	return direction[ 2 ];
}


