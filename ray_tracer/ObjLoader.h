/*
 * Mesh.h
 *
 *  Created on: 17.12.2015
 *      Author: Fabian Türk
 */

#ifndef OBJLOADER_H_
#define OBJLOADER_H_

#include <string>
#include "../libs/glm/glm/vec3.hpp"

class ObjLoader{
	ObjLoader( const ObjLoader& objLoader );
	ObjLoader& operator=( const ObjLoader& objLoader );
public:
	ObjLoader( std::string srcPath );
	virtual ~ObjLoader();
};



#endif /* OBJLOADER_H_ */
