/*
 * ImagePlane.h
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türk
 */

#ifndef IMAGEPLANE_H_
#define IMAGEPLANE_H_


class ImagePlane{
	ImagePlane( const ImagePlane& );
	ImagePlane& operator=( const ImagePlane& );
public:
	ImagePlane();
	virtual ~ImagePlane();
};



#endif /* IMAGEPLANE_H_ */
