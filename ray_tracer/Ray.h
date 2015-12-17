/*
 * Ray.h
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türk
 */

#ifndef RAY_H_
#define RAY_H_

#include <string>
#include "../libs/glm/glm/fwd.hpp"
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"

class Ray{
	glm::vec4 direction;
	float length;

public:
	Ray( );
	Ray( glm::vec4 direction );
	virtual ~Ray();
	Ray( const Ray& ray );
	Ray& operator=( const Ray& ray );
	std::string toString();
	std::string posToColorString();
	void normalize();
};



#endif /* RAY_H_ */
