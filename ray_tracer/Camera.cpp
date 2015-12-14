/*
 * Camera.cpp
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include "../libs/glm/glm/vec4.hpp"
#include "Camera.h"
using namespace std;

Camera::Camera(){
	position = glm::vec4 ( 0, 0, 0, 0 );
	up = glm::vec4 ( 0, 1, 0, 0 );
	horizontal_fov = 45;
	vertical_fov = 45;
};
Camera::~Camera(){ };
Camera::Camera( const Camera& ){
	position = glm::vec4 ( 0, 0, 0, 0 );
	up = glm::vec4 ( 0, 1, 0, 0 );
	horizontal_fov = 45;
	vertical_fov = 45;
};
Camera& Camera::operator=( const Camera& ){ return *this; };



