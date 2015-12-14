/*
 * Ray.cpp
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "Ray.h"
using namespace std;

Ray::Ray(){
	position = glm::vec4( 0, 0, 0, 0 );
	delta = 1;
};
Ray::~Ray(){ };
Ray::Ray( const Ray& ){
	position = glm::vec4( 0, 0, 0, 0 );
	delta = 1;
};
Ray& Ray::operator=( const Ray& ){ return *this; };


