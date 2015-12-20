/*
 * Mesh.h
 *
 *  Created on: 17.12.2015
 *      Author: Fabian Türk
 */

#ifndef MESH_H_
#define MESH_H_

#include <string>
#include "Surface.h"

class Mesh: public Surface{
	std::string srcName;

	Mesh( const Mesh& Mesh );
	Mesh& operator=( const Mesh& Mesh );
public:
	Mesh( glm::vec4 position, glm::vec3 color, glm::vec4 phong, float reflectance, float transmittance, float refraction, std::string srcName );
	virtual ~Mesh();

	virtual void initPhongIlluModel();
	virtual void transform();
	virtual void initTexture();

	void print();
};



#endif /* MESH_H_ */
