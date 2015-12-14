/*
 * Camera.h
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türks
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "../libs/glm/glm/fwd.hpp"
#include "../libs/glm/glm/vec4.hpp"

class Camera{
	glm::vec4 position;
	glm::vec4 up;
	float horizontal_fov;
	float vertical_fov;

	Camera( const Camera& );
	Camera& operator=( const Camera& );
public:
	Camera();
	virtual ~Camera();
};



#endif /* CAMERA_H_ */
