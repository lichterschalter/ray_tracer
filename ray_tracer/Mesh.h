/*
 * Mesh.h
 *
 *  Created on: 17.12.2015
 *      Author: Fabian Türk
 */

#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <vector>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "Surface.h"
#include "Triangle.h"

class Mesh: public Surface{
	std::string srcName;
	std::vector < Triangle > triangles;
	std::vector < glm::vec3 > v;
	std::vector < glm::vec3 > vt;
	std::vector < glm::vec3 > vn;
	std::string usemtl;
	int s;
	std::vector < std::vector < glm::vec3 > > f;
	//explaination f: first vector has all faces, one face has three points

public:
	Mesh( const Mesh& mesh );
	Mesh& operator=( const Mesh& mesh );
	Mesh( glm::vec4 position, glm::vec3 color, glm::vec4 phong, float reflectance, float transmittance, float refraction,
			std::string srcName, std::vector < glm::vec3 > v, std::vector < glm::vec3 > vt, std::vector < glm::vec3 > vn, std::string usemtl,
			int s, std::vector < std::vector < glm::vec3 > > f );
	virtual ~Mesh();

	void print();
	std::vector< Triangle > get_triangles();
};



#endif /* MESH_H_ */
