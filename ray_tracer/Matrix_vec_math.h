/*
 * Matrix_vec_math.h
 *
 *  Created on: 16.12.2015
 *      Author: Fabian Türk
 */

#ifndef Matrix_vec_math_H_
#define Matrix_vec_math_H_

#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "../libs/glm/glm/mat4x4.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/glm/gtx/string_cast.hpp"

class Matrix_vec_math{

	Matrix_vec_math( const Matrix_vec_math& );
	Matrix_vec_math& operator=( const Matrix_vec_math& );
public:
	Matrix_vec_math( );
	virtual ~Matrix_vec_math();
	glm::vec3 vec4ToVec3( glm::vec4 homogenVector );
	float lengthVec3( glm::vec3 Vector3 );
	glm::vec4 crossVec4(glm::vec4 _vec1, glm::vec4 _vec2);
	glm::vec4 normalize(glm::vec4 vector);
};



#endif /* Matrix_vec_math_H_ */
