/*
 * Surface.h
 *
 *  Created on: 17.12.2015
 *      Author: Fabian Türk
 */

#ifndef SURFACE_H_
#define SURFACE_H_

#include <string>
#include <iostream>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "../libs/glm/glm/gtx/string_cast.hpp"


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

	Surface( const Surface& surface ){
		position = surface.position;
		translate = surface.translate;
		scale = surface.scale;
		rotateX = surface.rotateX;
		rotateY = surface.rotateY;
		rotateZ = surface.rotateZ;
		phong = surface.phong;
		reflectance = surface.reflectance;
		transmittance = surface.transmittance;
		refraction = surface.refraction;
		normalVec = surface.normalVec;
		lightVec = surface.lightVec;
		eyeVec = surface.eyeVec;
		reflectanceVec = surface.reflectanceVec;
		textured = surface.textured;
		texture_name = surface.texture_name;
		color = surface.color;
	};
	Surface& operator=( const Surface& surface ){
		position = surface.position;
		translate = surface.translate;
		scale = surface.scale;
		rotateX = surface.rotateX;
		rotateY = surface.rotateY;
		rotateZ = surface.rotateZ;
		phong = surface.phong;
		reflectance = surface.reflectance;
		transmittance = surface.transmittance;
		refraction = surface.refraction;
		normalVec = surface.normalVec;
		lightVec = surface.lightVec;
		eyeVec = surface.eyeVec;
		reflectanceVec = surface.reflectanceVec;
		textured = surface.textured;
		texture_name = surface.texture_name;
		color = surface.color;
		return *this;
	};

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
	};
	virtual ~Surface(){ };

	void print(){
		std::cout << "position: " << glm::to_string(position) << std::endl;
		std::cout << "translate: " << glm::to_string(translate) << std::endl;
		std::cout << "scale: " << glm::to_string(scale) << std::endl;
		std::cout << "rotateX: " << glm::to_string(rotateX) << std::endl;
		std::cout << "rotateY: " << glm::to_string(rotateY) << std::endl;
		std::cout << "rotateZ: " << glm::to_string(rotateZ) << std::endl;
		std::cout << "phong: " << glm::to_string(phong) << std::endl;
		std::cout << "reflectance: " << reflectance << std::endl;
		std::cout << "transmittance: " << transmittance << std::endl;
		std::cout << "refraction: " << refraction << std::endl;
		std::cout << "normalVec: " << glm::to_string(normalVec) << std::endl;
		std::cout << "lightVec: " << glm::to_string(lightVec) << std::endl;
		std::cout << "eyeVec: " << glm::to_string(eyeVec) << std::endl;
		std::cout << "reflectanceVec: " << glm::to_string(reflectanceVec) << std::endl;
		std::cout << "textured: " << textured << std::endl;
		std::cout << "texture_name: " << texture_name << std::endl;
		std::cout << "color: " << glm::to_string(color) << std::endl;
	}
};


#endif /* SURFACE_H_ */
