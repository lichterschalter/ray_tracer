/*
 * Sphere.h
 *
 *  Created on: 17.12.2015
 *      Author: Fabian Türk
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include <string>
#include <vector>
#include "../libs/glm/glm/vec4.hpp"
#include "Surface.h"

class Sphere: public Surface{
	float radius;

public:
	Sphere( glm::vec4 position, glm::vec3 color, glm::vec4 phong, float reflectance, float transmittance, float refraction, float radius );
	Sphere( const Sphere& sphere );
	Sphere& operator=( const Sphere& sphere );
	virtual ~Sphere();

	void print();
	glm::vec3 get_color();
	glm::vec4 get_position();
	float get_radius();
	glm::vec4 get_phong();
};



#endif /* SPHERE_H_ */
