/*
 * Projection.h
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türks
 */

#ifndef PROJECTION_H_
#define PROJECTION_H_

#include <vector>
#include <string>
#include "../libs/glm/glm/fwd.hpp"
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "Ray.h"

class Projection{

	//Camera
	glm::vec4 posCamera;
	glm::vec4 upCamera;
	float horizontal_fov;
	float vertical_fov;

	//IMAGE PLANE
	glm::vec4 posImgPlaneCenter;
	glm::vec4 posImgPlaneTopLeft;
	glm::vec4 posImgPlaneBottomRight;
	int heightImgPlane;
	int widthImgPlane;
	std::vector< std::vector<std::string> > contentImgPlane;

	//RAY
	Ray ray;

	Projection( const Projection& );
	Projection& operator=( const Projection& );
public:
	Projection();
	virtual ~Projection();
	void print();
	void printContentImgPlane();
};



#endif /* PROJECTION_H_ */
