/*
 * Mesh.cpp
 *
 *  Created on: 17.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include <vector>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "../libs/glm/glm/gtx/string_cast.hpp"
#include "Mesh.h"
#include "Triangle.h"
using namespace std;

	Mesh::Mesh( glm::vec4 position, glm::vec3 color, glm::vec4 phong, float reflectance, float transmittance, float refraction, string srcName,
			vector < glm::vec3 > v, vector < glm::vec3 > vt, vector < glm::vec3 > vn, string usemtl,
			int s, vector < vector < glm::vec3 > > f )
	: Surface( color, phong, reflectance, transmittance, refraction ) {
		this->srcName = srcName;
		this->v = v;
		this->vt = vt;
		this->vn = vn;
		this->usemtl = usemtl;
		this->s = s;
		this->f = f;

		for( unsigned int i = 0; i < f.size(); ++i ){
			vector < glm::vec4 > vTemp;



			//Triangle triangle( v, vt, vn, usemtl, s, f );
			//triangles.push_back( triangle );
		}

		cout << "V: " << v.size() << " VT: " << vt.size() << " VN: " << vn.size() << " F: " << f.size() << endl;
	};
	Mesh::Mesh( const Mesh& mesh ) : Surface( mesh ) {
		this->srcName = mesh.srcName;
		this->triangles = mesh.triangles;
		this->v = mesh.v;
		this->vt = mesh.vt;
		this->vn = mesh.vn;
		this->usemtl = mesh.usemtl;
		this->s = mesh.s;
		this->f = mesh.f;
	};
	Mesh& Mesh::operator=( const Mesh& mesh ){ return *this; };
	Mesh::~Mesh(){ };

	void Mesh::print(){
		cout << endl << "--Mesh--" << endl;
		Surface::print();
		cout << "srcName: " << this->srcName << endl;

		cout << "triangles: ";
		for( unsigned int i = 0; i < triangles.size(); ++i ){
			triangles.at( i ).print();

		}

		cout << "v: ";
		for( unsigned int i = 0; i < v.size(); ++i ){
			cout << glm::to_string( v.at( i ) ) << " ";
		}
		cout << endl;

		cout << "vt: ";
		for( unsigned int i = 0; i < vt.size(); ++i ){
			cout << glm::to_string( vt.at( i ) ) << " ";
		}
		cout << endl;

		cout << "vn: ";
		for( unsigned int i = 0; i < vn.size(); ++i ){
			cout << glm::to_string( vn.at( i ) ) << " ";
		}
		cout << endl;

		cout << "usemtl: " << usemtl << endl;
		cout << "s: " << s << endl;

		cout << "f: ";
		for( unsigned int i = 0; i < f.size(); ++i ){
			for( unsigned int j = 0; j < f.at( i ).size(); ++j ){
				cout << glm::to_string( f.at( i ).at( j ) ) << " ";
			}
		}
		cout << endl;

		cout << "--end Mesh--" << endl;
		cout << endl;

	}


