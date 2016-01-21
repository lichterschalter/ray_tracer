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
	: Surface( color, phong, reflectance, transmittance, refraction ) {
		this->radius = radius;
		this->position = position;
	};
	Sphere::Sphere( const Sphere& sphere ) : Surface( sphere ) {
		this->radius = sphere.radius;
		this->position = sphere.position;
	};
	Sphere& Sphere::operator=( const Sphere& sphere ) {
		Surface::operator=( sphere );
		this->radius = radius;
		this->position = position;
		return *this;
	};
	Sphere::~Sphere(){ };

	void Sphere::print(){
		cout << endl << "--sphere--" << endl;
		cout << "position: " << glm::to_string(position) << std::endl;
		Surface::print();
		cout << "radius: " << this->radius << endl;
		cout << "--end sphere--" << endl;
		cout << endl;

	}

	glm::vec3 Sphere::get_color(){
		return color;
	}
	glm::vec4 Sphere::get_position(){
		return position;
	}
	float Sphere::get_radius(){
		return radius;
	}
	glm::vec4 Sphere::get_phong(){
		return phong;
	}


