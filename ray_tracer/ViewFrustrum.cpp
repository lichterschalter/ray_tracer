/*
 * Camera.cpp
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include "../libs/glm/glm/vec4.hpp"
#include "ViewFrustrum.h"
using namespace std;

Camera::Camera(){
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
	posRay = glm::vec4 ( 0, 0, 0, 0);
	deltaRay = 1;
};
Camera::~Camera(){ };
Camera::Camera( const Camera& ){
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
	posRay = glm::vec4 ( 0, 0, 0, 0);
	deltaRay = 1;
};
Camera& Camera::operator=( const Camera& ){ return *this; };



