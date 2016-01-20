/*
 * World.h
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türks
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include <string>
#include "../libs/glm/glm/fwd.hpp"
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "Ray.h"
#include "Sphere.h"
#include "Mesh.h"

class World{

	//World
	std::vector<Sphere> spheres;

	//Camera
	glm::vec4 posCamera;
	glm::vec4 upCamera;
	glm::vec4 lookAtCamera;
	glm::vec4 rightVec;
	float horizontal_fov;
	int maxBounces;

	//Image Plane
	glm::vec4 posImgPlaneTopLeft;
	int heightImgPlane;
	int widthImgPlane;
	double pixelWidth;
	double pixelHeight;
	std::vector< std::vector<std::string> > contentImgPlane;

	//Lights
	glm::vec3 ambientLight;
	glm::vec3 parallelLightCol;
	glm::vec3 parallelLightDir;
	std::vector < glm::vec3 > pointLightsCol;
	std::vector < glm::vec3 > pointLightsPos;

	//Background color
	glm::vec3 bgcolor;

	//Ray
	Ray ray;

	World( const World& );
	World& operator=( const World& );
public:
	World( glm::vec4 posCamera, glm::vec4 upCamera, glm::vec4 lookAtCamera, \
			double horizontal_fov, int maxBounces, int heightImgPlane, int widthImgPlane, glm::vec3 bgcolor,
			glm::vec3 ambientLight,	glm::vec3 parallelLightCol,	glm::vec3 parallelLightDir,
			std::vector < glm::vec3 > pointLightsCol, std::vector < glm::vec3 > pointLightsPos );
	virtual ~World();
	void createSphere( Sphere sphere );
	void createMesh( Mesh mesh );
	void print();
	void printContentImgPlane();
	std::string contentImgPlaneToString();
	int getWidthImgPlane();
	int getHeightImgPlane();
	void performRayTracing();
	glm::vec3 phongAmbient( glm::vec4 phong, glm::vec3 colorSurface );
	glm::vec3 phongDiffuse( glm::vec4 phong, float skalarNL, glm::vec3 colorSurface );
	glm::vec3 phongSpecular( glm::vec4 phong, float skalarRV );
};



#endif /* WORLD_H_ */
