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
	this->position = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
	this->delta = 1;
};
Ray::Ray( glm::vec4 position, float delta ){
	this->position = position;
	this->delta = delta;
};
Ray::~Ray(){ };
Ray::Ray( const Ray& ray ){
	this->position = ray.position;
	this->delta = ray.delta;
};
Ray& Ray::operator=( const Ray& ray ){
	this->position = ray.position;
	this->delta = ray.delta;
	return *this;
};

string Ray::toString(){
	string positionStr = glm::to_string(position);
	stringstream sstr;
	sstr << delta;
	string deltaStr = sstr.str();
	return "position: " + positionStr + "\n   delta: " + deltaStr;
}

string Ray::posToColorString(){
	/*
	stringstream sstrX, sstrY, sstrZ;
	unsigned int x, y, z;
	x = position[ 0 ] >= 0 ? position[ 0 ] : 0;
	y = position[ 1 ] >= 0 ? position[ 1 ] : 0;
	z = position[ 2 ] >= 0 ? position[ 2 ] : 0;
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
	x = position[ 0 ];
	y = position[ 1 ];
	z = position[ 2 ] >= 0 ? position[ 2 ] : 0;
	sstrX << abs(int(x));
	string posX = sstrX.str();
	sstrY << abs(int(y));
	string posY = sstrY.str();
	sstrZ << abs(int(z));
	string posZ = sstrZ.str();
	return posX + " " + posY + " " + posZ;
}


