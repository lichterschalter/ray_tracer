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
	float horizontal_fov;
	int maxBounces;

	//IMAGE PLANE
	glm::vec4 posImgPlaneTopLeft;
	int heightImgPlane;
	int widthImgPlane;
	std::vector< std::vector<std::string> > contentImgPlane;

	//Background color
	glm::vec3 bgcolor;

	//Ray
	Ray ray;

	World( const World& );
	World& operator=( const World& );
public:
	World( glm::vec4 posCamera, glm::vec4 upCamera, glm::vec4 lookAtCamera, \
			double horizontal_fov, int maxBounces, int heightImgPlane, int widthImgPlane, glm::vec3 bgcolor );
	virtual ~World();
	void createSphere( Sphere sphere );
	void createMesh( Mesh mesh );
	void print();
	void printContentImgPlane();
	std::string contentImgPlaneToString();
	int getWidthImgPlane();
	int getHeightImgPlane();
	void performRayTracing();
};



#endif /* WORLD_H_ */
