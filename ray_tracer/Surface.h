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
	glm::vec4 translate;
	glm::vec4 scale;
	glm::vec4 rotateX;
	glm::vec4 rotateY;
	glm::vec4 rotateZ;
	glm::vec4 phong;
	float reflectance;
	float transmittance;
	float refraction;
	bool textured;
	std::string texture_name;
	glm::vec3 color;

	Surface( const Surface& surface ){
		translate = surface.translate;
		scale = surface.scale;
		rotateX = surface.rotateX;
		rotateY = surface.rotateY;
		rotateZ = surface.rotateZ;
		phong = surface.phong;
		reflectance = surface.reflectance;
		transmittance = surface.transmittance;
		refraction = surface.refraction;
		textured = surface.textured;
		texture_name = surface.texture_name;
		color = surface.color;
	};
	Surface& operator=( const Surface& surface ){
		translate = surface.translate;
		scale = surface.scale;
		rotateX = surface.rotateX;
		rotateY = surface.rotateY;
		rotateZ = surface.rotateZ;
		phong = surface.phong;
		reflectance = surface.reflectance;
		transmittance = surface.transmittance;
		refraction = surface.refraction;
		textured = surface.textured;
		texture_name = surface.texture_name;
		color = surface.color;
		return *this;
	};

public:
	Surface( glm::vec3 color, glm::vec4 phong, float reflectance, float transmittance, float refraction ) {
		translate = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		scale = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		rotateX = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		rotateY = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		rotateZ = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
		this->phong = phong;
		this->reflectance = reflectance;
		this->transmittance = transmittance;
		this->refraction = refraction;
		textured = false;
		texture_name = "";
		this->color = color;
	};
	virtual ~Surface(){ };

	void print(){
		std::cout << "translate: " << glm::to_string(translate) << std::endl;
		std::cout << "scale: " << glm::to_string(scale) << std::endl;
		std::cout << "rotateX: " << glm::to_string(rotateX) << std::endl;
		std::cout << "rotateY: " << glm::to_string(rotateY) << std::endl;
		std::cout << "rotateZ: " << glm::to_string(rotateZ) << std::endl;
		std::cout << "phong: " << glm::to_string(phong) << std::endl;
		std::cout << "reflectance: " << reflectance << std::endl;
		std::cout << "transmittance: " << transmittance << std::endl;
		std::cout << "refraction: " << refraction << std::endl;
		std::cout << "textured: " << textured << std::endl;
		std::cout << "texture_name: " << texture_name << std::endl;
		std::cout << "color: " << glm::to_string(color) << std::endl;
	}

	float get_reflectance(){
		return reflectance;
	}
};


#endif /* SURFACE_H_ */
