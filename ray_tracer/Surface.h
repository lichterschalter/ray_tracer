/*
 * Surface.h
 *
 *  Created on: 17.12.2015
 *      Author: Fabian Türk
 */

#ifndef SURFACE_H_
#define SURFACE_H_

#include <string>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"


class Surface{
protected:
	glm::vec4 position;
	glm::vec4 translate;
	glm::vec4 scale;
	glm::vec4 rotateX;
	glm::vec4 rotateY;
	glm::vec4 rotateZ;
	glm::vec4 phong;
	float reflectance;
	float transmittance;
	float refraction;
	glm::vec4 normalVec;
	glm::vec4 lightVec;
	glm::vec4 eyeVec;
	glm::vec4 reflectanceVec;
	bool textured;
	std::string texture_name;
	glm::vec3 color;
	float radius;
	std::string src_name_mesh;

	Surface( const Surface& surface ){
		position = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		translate = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		scale = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		rotateX = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		rotateY = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		rotateZ = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		phong = glm::vec4( 0.3, 0.9, 1.0, 200.0 );
		reflectance = 1.0;
		transmittance = 0.0;
		refraction = 0.0;
		normalVec = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		lightVec = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		eyeVec = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		reflectanceVec = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		textured = false;
		texture_name = "";
		color = glm::vec3( 0.5, 0.17, 0.18 );
		radius = 1.0;
		src_name_mesh = "";
	};
	Surface& operator=( const Surface& ){ return *this; };

	virtual void initPhongIlluModel()= 0;
	virtual void transform() = 0;
	virtual void initTexture() = 0;
public:
	Surface( glm::vec4 position ) {
		this->position = position;
		translate = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		scale = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		rotateX = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		rotateY = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		rotateZ = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		phong = glm::vec4( 0.3, 0.9, 1.0, 200.0 );
		reflectance = 1.0;
		transmittance = 0.0;
		refraction = 0.0;
		normalVec = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		lightVec = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		eyeVec = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		reflectanceVec = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		textured = false;
		texture_name = "";
		color = glm::vec3( 0.5, 0.17, 0.18 );
		radius = 1.0;
		src_name_mesh = "";
	};
	virtual ~Surface(){ };
};


#endif /* SURFACE_H_ */
