/*
 * Camera.h
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türks
 */

#ifndef CAMERA_H_
#define CAMERA_H_

class Camera{
	Camera( const Camera& );
	Camera& operator=( const Camera& );
public:
	Camera();
	virtual ~Camera();
};



#endif /* CAMERA_H_ */
