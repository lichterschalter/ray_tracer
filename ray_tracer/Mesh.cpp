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

		//1. create for every face f a triangle
		for( unsigned int i = 0; i < f.size(); ++i ){

			//2. set the points (v,vt,vn) of the triangle with f
			vector < glm::vec3 > vTemp;
			vector < glm::vec3 > vtTemp;
			glm::vec3 vnTemp = vn.at( f.at( i ).at( 0 )[ 2 ] - 1 );
			int k = 0;
			for( unsigned int j = 0; j < f.at( i ).size(); ++j ){
				vTemp.push_back( v.at( f.at( i ).at( k )[ 0 ] - 1 ) );
				vtTemp.push_back( vt.at( f.at( i ).at( k )[ 1 ] - 1 ) );
				++k;
			}

			//3. initialize triangle
			Triangle triangle( vTemp, vtTemp, vnTemp, usemtl, s );
			triangles.push_back( triangle );
		}
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

		cout << "triangles: " << endl;
		cout << "___________" << endl << endl;
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

	std::vector< Triangle > Mesh::get_triangles(){
		return triangles;
	}

	glm::vec4 Mesh::get_phong(){
		return phong;
	}

	glm::vec3 Mesh::get_color(){
		return color;
	}

