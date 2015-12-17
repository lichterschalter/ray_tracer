/*
 * Sphere.h
 *
 *  Created on: 17.12.2015
 *      Author: rustong_pu
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include <string>
#include "Surface.h"

class Sphere: public Surface{
	float radius;

	Sphere( const Sphere& sphere );
	Sphere& operator=( const Sphere& sphere );
public:
	Sphere(glm::vec4 position, float radius );
	virtual ~Sphere();

	virtual void initPhongIlluModel();
	virtual void transform();
	virtual void initTexture();
};



#endif /* SPHERE_H_ */
