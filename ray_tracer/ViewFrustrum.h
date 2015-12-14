/*
 * Camera.h
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türks
 */

#ifndef VIEWFRUSTRUM_H_
#define VIEWFRUSTRUM_H_

#include "../libs/glm/glm/fwd.hpp"
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"

class Camera{
	glm::vec4 posCamera;
	glm::vec4 upCamera;
	float horizontal_fov;
	float vertical_fov;
	glm::vec4 posImgPlaneCenter;
	glm::vec4 posImgPlaneTopLeft;
	glm::vec4 posImgPlaneBottomRight;
	int heightImgPlane;
	int widthImgPlane;
	//glm::vec3[][] contentImgPlane;
	glm::vec4 posRay;
	float deltaRay;



	Camera( const Camera& );
	Camera& operator=( const Camera& );
public:
	Camera();
	virtual ~Camera();
};



#endif /* VIEWFRUSTRUM_H_ */
