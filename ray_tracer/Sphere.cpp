/*
 * Sphere.cpp
 *
 *  Created on: 17.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include "Sphere.h"
using namespace std;

	Sphere::Sphere( glm::vec4 position, float radius ) : Surface( position ) {
		this->radius = radius;
	};
	Sphere::Sphere( const Sphere& sphere ) : Surface( sphere ) {
		this->radius = sphere.radius;
	};
	Sphere& Sphere::operator=( const Sphere& sphere ){ return *this; };
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


