/*
 * Sphere.cpp
 *
 *  Created on: 17.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include "../libs/glm/glm/vec4.hpp"
#include "Sphere.h"
using namespace std;

	Sphere::Sphere( glm::vec4 position, glm::vec3 color, glm::vec4 phong, float reflectance, float transmittance, float refraction, float radius )
	: Surface( position, color, phong, reflectance, transmittance, refraction ) {
		this->radius = radius;
	};
	Sphere::Sphere( const Sphere& sphere ) : Surface( sphere ) {
		this->radius = sphere.radius;
	};
	Sphere& Sphere::operator=( const Sphere& sphere ) {
		Surface::operator=( sphere );
		this->radius = radius;
		return *this;
	};
	Sphere::~Sphere(){ };


	void Sphere::initPhongIlluModel(){
	}
	void Sphere::transform(){
	}
	void Sphere::initTexture(){
	}

	void Sphere::print(){
		cout << endl << "--sphere--" << endl;
		Surface::print();
		cout << "radius: " << this->radius << endl;
		cout << "--end sphere--" << endl;
		cout << endl;

	}


