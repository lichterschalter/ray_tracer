/*
 * Triangle.cpp
 *
 *  Created on: 21.01.2016
 *      Author: Fabian Türk
 */

#include <iostream>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "../libs/glm/glm/mat4x4.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/glm/gtx/string_cast.hpp"
#include "Triangle.h"
using namespace std;

Triangle::Triangle( std::vector< glm::vec3 > v, std::vector< glm::vec3 > vt, glm::vec3 vn, std::string usemtl, int s ){
	this->v = v;
	this->vt = vt;
	this->vn = vn;
	this->usemtl = usemtl;
	this->s = s;

}
Triangle::Triangle( const Triangle& triangle ){
	this->v = triangle.v;
	this->vt = triangle.vt;
	this->vn = triangle.vn;
	this->usemtl = triangle.usemtl;
	this->s = triangle.s;
}
Triangle& Triangle::operator=( const Triangle& ){
	return *this;
}

Triangle::~Triangle() { };

void Triangle::print() {
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

	cout << "vn: " << glm::to_string( vn ) << " ";

	cout << endl;

	cout << "usemtl: " << usemtl << endl;
	cout << "s: " << s << endl;
	cout << "___________" << endl << endl;
}


