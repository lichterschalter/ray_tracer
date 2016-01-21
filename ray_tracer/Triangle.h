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
	std::vector < glm::vec4 > v;
	std::vector < glm::vec4 > vt;
	glm::vec4 vn;
	std::string usemtl;
	int s;
public:
	Triangle( std::vector< glm::vec4 > v, std::vector< glm::vec4 > vt, glm::vec4 vn, std::string usemtl, int s, glm::vec3 f );
	Triangle( const Triangle& );
	Triangle& operator=( const Triangle& );
	virtual ~Triangle();
	void print();
};



#endif /* TRIANGLE_H_ */
