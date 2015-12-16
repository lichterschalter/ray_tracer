/*
 * Matrix_vec_math.cpp
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türk
 */

#include <iostream>
#include <cmath>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "../libs/glm/glm/mat4x4.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/glm/gtx/string_cast.hpp"
#include "Matrix_vec_math.h"
using namespace std;

Matrix_vec_math::Matrix_vec_math(){ };
Matrix_vec_math::~Matrix_vec_math(){ };
Matrix_vec_math::Matrix_vec_math( const Matrix_vec_math& ){ };
Matrix_vec_math& Matrix_vec_math::operator=( const Matrix_vec_math& ){ return *this; };

glm::vec3 Matrix_vec_math::vec4ToVec3( glm::vec4 homogenVector ){
	glm::vec3 nothomogenVector;
	nothomogenVector[ 0 ] = ( homogenVector[ 0 ] / homogenVector[ 3 ] );
	nothomogenVector[ 1 ] = ( homogenVector[ 1 ] / homogenVector[ 3 ] );
	nothomogenVector[ 2 ] = ( homogenVector[ 2 ] / homogenVector[ 3 ] );
	return nothomogenVector;
}

float Matrix_vec_math::lengthVec3( glm::vec3 Vector3 ){
	return sqrt( pow( Vector3[ 0 ], 2 ) + pow( Vector3[ 1 ], 2 ) + pow( Vector3[ 2 ], 2 ) );
}





