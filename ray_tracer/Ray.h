/*
 * Ray.h
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türk
 */

#ifndef RAY_H_
#define RAY_H_

class Ray{
	Ray( const Ray& );
	Ray& operator=( const Ray& );
public:
	Ray();
	virtual ~Ray();
};




#endif /* RAY_H_ */
