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
#include "../libs/glm/glm/geometric.hpp"
#include "Triangle.h"
using namespace std;

Triangle::Triangle( std::vector< glm::vec3 > v, std::vector< glm::vec3 > vt, glm::vec3 vn, std::string usemtl, int s ){
	this->v = v;
	this->vt = vt;
	this->vn = vn;
	this->usemtl = usemtl;
	this->s = s;

	e12 = v.at( 0 ) - v.at( 1 );
	e13 = v.at( 0 ) - v.at( 2 );
	n = glm::normalize( glm::cross( e12, e13 ) );

}
Triangle::Triangle( const Triangle& triangle ){
	this->v = triangle.v;
	this->vt = triangle.vt;
	this->vn = triangle.vn;
	this->usemtl = triangle.usemtl;
	this->s = triangle.s;
	this->e12 = triangle.e12;
	this->e13 = triangle.e13;
	this->n = triangle.n;
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
	cout << "e12: " << glm::to_string( e12 ) << endl;
	cout << "e13: " << glm::to_string( e13 ) << endl;
	cout << "n: " << glm::to_string( n ) << endl;
	cout << "___________" << endl << endl;
}

std::vector < glm::vec3 > Triangle::get_v(){
	return v;
}
std::vector < glm::vec3 > Triangle::get_vt(){
	return vt;
}
glm::vec3 Triangle::get_vn(){
	return vn;
}
std::string Triangle::get_usemtl(){
	return usemtl;
}
int Triangle::get_s(){
	return s;
}
glm::vec3 Triangle::get_n(){
	return n;
}


