/*
 * Triangle.h
 *
 *  Created on: 21.01.2016
 *      Author: Fabian Türk
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <vector>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"

class Triangle{
	std::vector < glm::vec3 > v;
	std::vector < glm::vec3 > vt;
	glm::vec3 vn;
	std::string usemtl;
	int s;
	glm::vec3 e12;
	glm::vec3 e13;
	glm::vec3 n; //(e12 x e13 / ||e12 x e13|| )
public:
	Triangle( std::vector< glm::vec3 > v, std::vector< glm::vec3 > vt, glm::vec3 vn, std::string usemtl, int s );
	Triangle( const Triangle& );
	Triangle& operator=( const Triangle& );
	virtual ~Triangle();
	void print();

	std::vector < glm::vec3 > get_v();
	std::vector < glm::vec3 > get_vt();
	glm::vec3 get_vn();
	std::string get_usemtl();
	int get_s();
	glm::vec3 get_e12();
	glm::vec3 get_e13();
	glm::vec3 get_n();
};



#endif /* TRIANGLE_H_ */
