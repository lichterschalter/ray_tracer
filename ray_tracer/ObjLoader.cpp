/*
 * ObjLoader.cpp
 *
 *  Created on: 20.01.2016
 *      Author: Fabian Türk
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cerrno>
#include <cstring>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/gtx/string_cast.hpp"
#include "ObjLoader.h"
using namespace std;

ObjLoader::ObjLoader( std::string srcPath ) {
	string line;
	string v;
	vector< glm::vec3 > vertices;

	ifstream myfile ( srcPath );
	if( myfile ){
		cout << "Opening .obj file \'" << srcPath << "\' was successfull." << endl;
		while( !myfile.eof() ) {
			getline ( myfile, line );
			if ( line[ 0 ] == 'v' && line[ 1 ] != 't' && line[ 1 ] != 'n' )
			{
				vector< string > verticesStr ( 3 );
				glm::vec3 verticeTemp;
				std::istringstream iss( line );
				iss >> v;
				iss >> verticesStr.at( 0 ) >> verticesStr.at( 1 ) >> verticesStr.at( 2 );
				for( unsigned int i = 0; i < verticesStr.size(); ++i ){
					verticeTemp[ i ] = atof( verticesStr[ i ].c_str() );
				}
				cout << glm::to_string( verticeTemp ) << endl;
			}
		}
	}else{
		cerr << "Loading .obj file \'" << srcPath << "\' failed!" << endl;
		cerr << "Error code: " << strerror(errno) << endl;
	}
}
ObjLoader::ObjLoader( const ObjLoader& objLoader ) { }
ObjLoader& ObjLoader::operator=( const ObjLoader& objLoader ) {
	return *this;
}
ObjLoader::~ObjLoader() { }


