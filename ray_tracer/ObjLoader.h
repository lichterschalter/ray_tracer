/*
 * Mesh.h
 *
 *  Created on: 17.12.2015
 *      Author: Fabian Türk
 */

#ifndef OBJLOADER_H_
#define OBJLOADER_H_

#include <string>
#include <vector>
#include "../libs/glm/glm/vec3.hpp"

class ObjLoader{
	std::string srcName;
	std::vector < glm::vec3 > v;
	std::vector < glm::vec3 > vt;
	std::vector < glm::vec3 > vn;
	std::string usemtl;
	int s;
	std::vector < std::vector < glm::vec3 > > f;
	//explaination f: first vector has all faces, one face has three points

	ObjLoader( const ObjLoader& objLoader );
	ObjLoader& operator=( const ObjLoader& objLoader );
public:
	ObjLoader( std::string srcPath );
	virtual ~ObjLoader();

	std::vector < glm::vec3 > get_v();
	std::vector < glm::vec3 > get_vt();
	std::vector < glm::vec3 > get_vn();
	std::string get_usemtl();
	int get_s();
	std::vector < std::vector < glm::vec3 > > get_f();
};



#endif /* OBJLOADER_H_ */
