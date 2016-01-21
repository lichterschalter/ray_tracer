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
public:
	Triangle( std::vector< glm::vec3 > v, std::vector< glm::vec3 > vt, glm::vec3 vn, std::string usemtl, int s );
	Triangle( const Triangle& );
	Triangle& operator=( const Triangle& );
	virtual ~Triangle();
	void print();
};



#endif /* TRIANGLE_H_ */
