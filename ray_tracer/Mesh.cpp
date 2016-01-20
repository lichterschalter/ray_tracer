/*
 * Mesh.cpp
 *
 *  Created on: 17.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include "Mesh.h"
using namespace std;

	Mesh::Mesh( glm::vec4 position, glm::vec3 color, glm::vec4 phong, float reflectance, float transmittance, float refraction, string srcName )
	: Surface( position, color, phong, reflectance, transmittance, refraction ) {
		this->srcName = srcName;
	};
	Mesh::Mesh( const Mesh& Mesh ) : Surface( Mesh ) {
		this->srcName = Mesh.srcName;
	};
	Mesh& Mesh::operator=( const Mesh& Mesh ){ return *this; };
	Mesh::~Mesh(){ };

	void Mesh::print(){
		cout << endl << "--Mesh--" << endl;
		Surface::print();
		cout << "srcName: " << this->srcName << endl;
		cout << "--end Mesh--" << endl;
		cout << endl;

	}


