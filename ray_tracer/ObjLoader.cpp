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
	string flag;

	ifstream myfile ( srcPath );
	if( myfile ){
		cout << "Opening .obj file \'" << srcPath << "\' was successfull." << endl;
		while( !myfile.eof() ) {
			getline ( myfile, line );

			//processing 'v', 'vt', 'vn'
			if ( line[ 0 ] == 'v' ) {
				vector< string > verticesStr ( 3 );
				glm::vec3 verticeTemp;
				std::istringstream iss( line );
				iss >> flag;
				iss >> verticesStr.at( 0 ) >> verticesStr.at( 1 ) >> verticesStr.at( 2 );
				for( unsigned int i = 0; i < verticesStr.size(); ++i ){
					verticeTemp[ i ] = atof( verticesStr.at( i ).c_str() );
				}

				if( line[ 1 ] != 't' && line[ 1 ] != 'n' ){ //save 'v'
					v.push_back( verticeTemp );
				}
				if( line[ 1 ] == 't' ){ //save 'vt'
					vt.push_back( verticeTemp );
				}
				if( line[ 1 ] == 'n' ){ //save 'vn'
					vn.push_back( verticeTemp );
				}
			}

			//processing 'usemtl'
			if( line[ 0 ] == 'u' && line[ 1 ] == 's' && line[ 2 ] == 'e' && line[ 4 ] == 'm' && line[ 5 ] == 't' && line[ 6 ] == 'l' ){
				std::istringstream iss( line );
				iss >> flag;
				iss >> usemtl;
			}

			//processing 's'
			if( line[ 0 ] == 's' ){
				std::istringstream iss( line );
				iss >> flag;
				iss >> s;
			}

			//processing 'f'
			if( line[ 0 ] == 'f' ){
				glm::vec3 trippleTemp;
				vector < glm::vec3 > fTemp;

				int k = 0;
				string number;
				for( unsigned int i = 2; i <= line.size(); ++i ){

					if( isdigit( line[ i ] ) ){
						number.push_back( line[ i ] );
					}
					if( line[ i ] == '/' ){
						trippleTemp[ k ] = atof( number.c_str() );
						number.clear();
						++k;
					}
					if( line[ i ] == ' ' || ( i + 1 ) == line.size() ){
						trippleTemp[ k ] = atof( number.c_str() );
						fTemp.push_back( trippleTemp );
						number.clear();
						k = 0;
					}
				}

				f.push_back( fTemp );
			}// end processing f
		}
	}else{
		cerr << "Loading .obj file \'" << srcPath << "\' failed!" << endl;
		cerr << "Error code: " << strerror(errno) << endl;
	}
}
ObjLoader::ObjLoader( const ObjLoader& objLoader ) {
	cout <<  "Warning: you use the ObjLoader copy constructor!" << endl;

	this->v = objLoader.v;
	this->vt = objLoader.vt;
	this->vn = objLoader.vn;
	this->usemtl = objLoader.usemtl;
	this->s = objLoader.s;
	this->f = objLoader.f;

}
ObjLoader& ObjLoader::operator=( const ObjLoader& objLoader ) {
	return *this;
}
ObjLoader::~ObjLoader() { }

std::vector < glm::vec3 > ObjLoader::get_v(){
	return v;
}
std::vector < glm::vec3 > ObjLoader::get_vt(){
	return vt;
}
std::vector < glm::vec3 > ObjLoader::get_vn(){
	return vn;
}
std::string ObjLoader::get_usemtl(){
	return usemtl;
}
int ObjLoader::get_s(){
	return s;
}
std::vector < std::vector < glm::vec3 > > ObjLoader::get_f(){
	return f;
}




