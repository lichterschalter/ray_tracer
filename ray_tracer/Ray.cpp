/*
 * Ray.cpp
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include <string>
#include <sstream>
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

std::string Ray::toString(){
	string positionStr = glm::to_string(position);
	stringstream sstr;
	sstr << delta;
	string deltaStr = sstr.str();
	return "position: " + positionStr + "\n   delta: " + deltaStr;
}


