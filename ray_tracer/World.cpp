/*
 * World.cpp
 *
 *  Created on: 14.12.2015
 *      Author: Fabian Türk
 */



#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "../libs/glm/glm/vec3.hpp"
#include "../libs/glm/glm/vec4.hpp"
#include "../libs/glm/glm/mat4x4.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/glm/gtx/string_cast.hpp"
#include "Matrix_vec_math.h"
#include "World.h"
#include "Sphere.h"
#include "Mesh.h"
using namespace std;

World::World( glm::vec4 posCamera, glm::vec4 upCamera, glm::vec4 lookAtCamera, \
		double horizontal_fov, int maxBounces, int heightImgPlane, int widthImgPlane, glm::vec3 bgcolor,
		glm::vec3 ambientLight,	glm::vec3 parallelLightCol,	glm::vec3 parallelLightDir,
		std::vector < glm::vec3 > pointLightsCol, std::vector < glm::vec3 > pointLightsPos ){

	cout << "Building the world. ";

	//INIT VARS FROM PARAMETERS
	this->posCamera = posCamera;
	this->upCamera = upCamera;
	this->lookAtCamera = lookAtCamera;
	this->horizontal_fov = horizontal_fov;
	this->heightImgPlane = heightImgPlane;
	this->widthImgPlane = widthImgPlane;
	this->maxBounces = maxBounces;
	this->bgcolor = bgcolor;
	this->ambientLight = ambientLight;
	this->parallelLightCol = parallelLightCol;
	this->parallelLightDir = parallelLightDir;
	this->pointLightsCol = pointLightsCol;
	this->pointLightsPos = pointLightsPos;


	//COMPUTE TOPLEFT AND BOTTOMRIGHT OF IMGPLANE

	//1. calculate points and vectors to reach topleft from poscamera
	Matrix_vec_math matrixvecmath;

	glm::vec4 dir( lookAtCamera[ 0 ] - posCamera[ 0 ], lookAtCamera[ 1 ] - posCamera[ 1 ], lookAtCamera[ 2 ] - posCamera[ 2 ], 1.0 );
	dir = matrixvecmath.normalize( dir );
	upCamera = matrixvecmath.normalize( upCamera );
	rightVec = matrixvecmath.crossVec4( dir, upCamera );
	rightVec = matrixvecmath.normalize( rightVec );
	upCamera = matrixvecmath.crossVec4( rightVec, dir );
	upCamera = matrixvecmath.normalize( upCamera );

	double pi = 3.1415926535897;
	float width = 2 * ( tan (horizontal_fov * pi / 180.0 ) * matrixvecmath.lengthVec4( dir ) );
	float height = width / ( widthImgPlane / heightImgPlane );

	glm::vec3 lookAtTemp = matrixvecmath.vec4ToVec3( lookAtCamera );
	glm::vec3 rightVecTemp = matrixvecmath.vec4ToVec3( rightVec );
	glm::vec3 upCameraTemp = matrixvecmath.vec4ToVec3( upCamera );

	pixelWidth = ( width / widthImgPlane );
	pixelHeight = ( height / heightImgPlane );

	glm::vec3 topLeftTemp = lookAtTemp + ( width / 2 * ( -rightVecTemp ) ) + ( height / 2 * ( upCameraTemp ) );
	posImgPlaneTopLeft = matrixvecmath.vec3ToVec4( topLeftTemp );
	posImgPlaneTopLeft[ 0 ] += pixelWidth / 2;
	posImgPlaneTopLeft[ 1 ] -= pixelHeight / 2;


	//FILL CONTENT OF IMGPLANE WITH BLACK PIXELS (use contentImgPlane[row][column])
	for (int i = 0; i < heightImgPlane; i++) {
		contentImgPlane.push_back(vector<string>()); // Add one empty row
	}
	for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    for (int j = 0; j < widthImgPlane; j++) {
	    	contentImgPlane.at( i ).push_back( "0 0 0  " ); // Add column to every rows
	    }
	}

	cout << "World creation was successfull." << endl;

};
World::~World(){ };
World::World( const World& world){
	cerr << "WARNING: Copy constructor should not be used!" << endl;

	//INIT VARS FROM PARAMETERS
	this->spheres = world.spheres;
	this->posCamera = world.posCamera;
	this->upCamera = world.upCamera;
	this->lookAtCamera = world.lookAtCamera;
	this->horizontal_fov = world.horizontal_fov;
	this->heightImgPlane = world.heightImgPlane;
	this->widthImgPlane = world.widthImgPlane;
	this->posImgPlaneTopLeft = world.posImgPlaneTopLeft;
	this->maxBounces = world.maxBounces;
	this->bgcolor = world.bgcolor;
	this->pixelWidth = world.pixelWidth;
	this->pixelHeight = world.pixelHeight;
	this->ambientLight = world.ambientLight;
	this->parallelLightCol = world.parallelLightCol;
	this->parallelLightDir = world.parallelLightDir;
	this->pointLightsCol = world.pointLightsCol;
	this->pointLightsPos = world.pointLightsPos;

};
World& World::operator=( const World& ){
	cerr << "WARNING: Copy assignment operator should not be used!" << endl;
	return *this;
};

void World::createSphere( Sphere sphere ){
	spheres.push_back( sphere );
}
void World::createMesh( Mesh mesh ){
	;
}

void World::print(){
	cout << endl;
	cout << "----begin class World----" << endl;
	cout << "posCamera: " << glm::to_string(posCamera) << endl;
	cout << "upCamera: " << glm::to_string(upCamera) << endl;
	cout << "lookAtCamera: " << glm::to_string(lookAtCamera) << endl;
	cout << "horizontal_fov: " << horizontal_fov << endl;
	cout << "maxBounces: " << maxBounces << endl;
	cout << "posImgPlaneTopLeft: " << glm::to_string(posImgPlaneTopLeft) << endl;
	cout << "heightImgPlane: " << heightImgPlane << endl;
	cout << "contentImgPlane: [is not printed, use printContentImgPlane() to print it]" << endl;
	cout << "ray: \n [ " << ray.toString() << " ]"<< endl;
	cout << "bgcolor: " << glm::to_string(bgcolor) << endl;

	cout << "ambientLight: " << to_string( ambientLight ) << endl;
	cout << "parallelLightCol: " << to_string( parallelLightCol ) << endl;
	cout << "parallelLightDir: " << to_string( parallelLightDir ) << endl;

	for( unsigned int i = 0; i < pointLightsCol.size() && i < pointLightsPos.size(); ++i ){
		cout << "--pointLight Nr. " << i + 1 << "--" << endl;
		stringstream sstr;
		sstr << to_string( pointLightsCol.at( i ) );
		cout << "pointLightCol: " << sstr.str() << " " << endl;

		stringstream sstr2;
		sstr2 << to_string( pointLightsPos.at( i ) );
		cout << "pointLightPos: " << sstr2.str() << " " << endl;
		cout << "----" << endl;
	}

	for( unsigned int i = 0; i < spheres.size(); ++i ){
		spheres.at( i ).print();
	}

	cout << "----end class World----" << endl << endl;
}

void World::printContentImgPlane(){
	for (int j = 0; j < widthImgPlane; j++){
		cout << "    " << j << ":       ";
	}
	cout << endl;
	for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
		cout << i << ": ";
	    for (int j = 0; j < widthImgPlane; j++) {
	    	cout << "| " << contentImgPlane.at( i ).at( j ) << " |  ";
	    }
	    cout << endl;
	}
}

string World::contentImgPlaneToString(){
	string outputString;

	for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    for (int j = 0; j < widthImgPlane; j++) {
	    	outputString.append( contentImgPlane.at( i ).at( j ) );
	    }
	    outputString.append("\n");
	}
	return outputString;
}

int World::getWidthImgPlane(){
	return widthImgPlane;
}

int World::getHeightImgPlane(){
	return heightImgPlane;
}

void World::performRayTracing(){
	Matrix_vec_math matrixvecmath;
	cout << "Shooting rays into the world..." << endl;


	//TEST SPHERE FOR DEBUGGING

	//glm::vec3 posSphere( 0.0, 0.0, -3.0 );
	//float radiusSphere = 1;

	//SHOOT RAYS TO THE CENTER OF EVERY PIXEL ON THE IMAGE PLANE

	contentImgPlane.clear();
	for (int i = 0; i < heightImgPlane; i++) {
		contentImgPlane.push_back(vector<string>()); // Add one empty row
	}

	for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    for (int j = 0; j < widthImgPlane; j++) {

	    	//0. calculate direction of ray
	    	glm::vec4 posRayOnPlane = posImgPlaneTopLeft;
			posRayOnPlane[ 0 ] = posRayOnPlane[ 0 ] + j * rightVec[ 0 ] * pixelWidth - i * (upCamera[ 0 ]) * pixelHeight;
			posRayOnPlane[ 1 ] = posRayOnPlane[ 1 ] + j * rightVec[ 1 ] * pixelWidth - i * (upCamera[ 1 ]) * pixelHeight;
			posRayOnPlane[ 2 ] = posRayOnPlane[ 2 ] + j * rightVec[ 2 ] * pixelWidth - i * (upCamera[ 2 ]) * pixelHeight;
	    	this->ray = Ray( glm::vec4(
	    			posRayOnPlane[ 0 ] - posCamera[ 0 ],
					posRayOnPlane[ 1 ] - posCamera[ 1 ],
					posRayOnPlane[ 2 ] - posCamera[ 2 ],
					1.0 )
			);
			//cout << "i: " << i << " j: " << j << endl;
	    	//cout << ray.toString() << endl;
			ray.normalize();


			//1. perform intersection test ray-sphere
			vector< float > intersections;
			vector< Sphere > intersectedSpheres;
			for( unsigned int i = 0; i < spheres.size(); ++i ){
				glm::vec4 posSphere( spheres.at( i ).get_position() );
				float radiusSphere = spheres.at( i ).get_radius();
				float a =  ray.getX() * ray.getX() +
						   ray.getY() * ray.getY() +
						   ray.getZ() * ray.getZ();

				float b =  ( 2 * posCamera[ 0 ] * ray.getX() - 2 * posSphere[ 0 ] * ray.getX() ) +
						   ( 2 * posCamera[ 1 ] * ray.getY() - 2 * posSphere[ 1 ] * ray.getY() ) +
						   ( 2 * posCamera[ 2 ] * ray.getZ() - 2 * posSphere[ 2 ] * ray.getZ() );

				float c = pow ( posCamera[ 0 ] - posSphere[ 0 ], 2 ) +
						  pow ( posCamera[ 1 ] - posSphere[ 1 ], 2 ) +
						  pow ( posCamera[ 2 ] - posSphere[ 2 ], 2 ) -
						  pow ( radiusSphere, 2 );
				float intersection = pow( b, 2 ) - 4 * a * c;
				if( intersection >= 0 ){
					float deltaOne = ( -b + sqrt( intersection ) ) / 2 * a;
					float deltaTwo = ( -b - sqrt( intersection ) ) / 2 * a;
					if( deltaOne <= deltaTwo ) intersections.push_back( deltaOne );
					if( deltaOne > deltaTwo ) intersections.push_back( deltaTwo );

					intersectedSpheres.push_back( spheres.at( i ) );
				}
			}

			/*
			cout << "INTERSECTIONS: " << endl;
			for( unsigned int i = 0; i < intersections.size(); ++i ){
				cout << intersections.at( i ) << endl;
			}
			*/

			//2.a there is an intersection
			if( intersections.size() != 0 ){

				//find biggest lambda
				int indexSmallest = 0;
				for( unsigned int i = 0; i < intersections.size(); ++i ){
					float* smallest = &intersections.at( i );
					for( unsigned int j = 1; j < intersections.size() - i; ++j ){
						float* smaller = &intersections.at( i + j );
						if( *smallest > *smaller ){
							indexSmallest = j;
							//float temp = *smaller;
							//*smaller = *biggest;
							*smallest = *smaller;
						}
					}
				}


				//phong shading
				glm::vec4 phong = intersectedSpheres.at( indexSmallest ).get_phong();
				glm::vec3 colorSurface = intersectedSpheres.at( indexSmallest ).get_color();

				glm::vec3 phong_ka = phongAmbient( phong, colorSurface );
				glm::vec3 phong_kd( 0.0, 0.0, 0.0 );
				glm::vec3 phong_ks( 0.0, 0.0, 0.0 );

				glm::vec3 phongPixel = phong_ka; //the sum of all shading therms

				glm::vec3 intersectPoint(
						posCamera[ 0 ] + intersections.at( indexSmallest ) * ray.getX(),
						posCamera[ 1 ] + intersections.at( indexSmallest ) * ray.getY(),
						posCamera[ 2 ] + intersections.at( indexSmallest ) * ray.getZ()
				);
				glm::vec4 sphereNormal =  matrixvecmath.vec3ToVec4( intersectPoint - matrixvecmath.vec4ToVec3( intersectedSpheres.at( indexSmallest ).get_position() ) / intersectedSpheres.at( indexSmallest ).get_radius() );
				sphereNormal = matrixvecmath.normalize( sphereNormal );
				glm::vec4 view = matrixvecmath.vec3ToVec4( matrixvecmath.vec4ToVec3( posCamera ) - intersectPoint );
				view = matrixvecmath.normalize( view );

				//phong_kd, phong_ks for parallel light
				if( parallelLightDir[ 0 ] != 0 || parallelLightDir[ 1 ] != 0 || parallelLightDir[ 2 ] != 0 ){
					glm::vec4 lightVec( -parallelLightDir[ 0 ], -parallelLightDir[ 1 ], -parallelLightDir[ 2 ], 1.0 );
					lightVec = matrixvecmath.normalize( lightVec );
					float skalarNL = sphereNormal[ 0 ] * lightVec[ 0 ] + sphereNormal[ 1 ] * lightVec[ 1 ] + sphereNormal[ 2 ] * lightVec[ 2 ];
					glm::vec4 reflectVec(
							2 * skalarNL * sphereNormal[ 0 ] - lightVec[ 0 ],
							2 * skalarNL * sphereNormal[ 1 ] - lightVec[ 1 ],
							2 * skalarNL * sphereNormal[ 2 ] - lightVec[ 2 ],
							1.0
					);
					reflectVec = matrixvecmath.normalize( reflectVec );
					float skalarRV = reflectVec[ 0 ] * view[ 0 ] + reflectVec[ 1 ] * view[ 1 ] + reflectVec[ 2 ] * view[ 2 ];

					phong_kd = phongDiffuse( phong, colorSurface, skalarNL );
					phong_ks = phongSpecular( phong, skalarRV );
					phongPixel += phong_kd + phong_ks;
				}

				//phong_kd, phong_ks for point light(s)
				for( unsigned int i = 0; i < pointLightsCol.size(); ++i ){
					glm::vec3 lightPos = pointLightsPos.at( i );
					glm::vec4 lightVec(
							lightPos[ 0 ] - intersectPoint[ 0 ],
							lightPos[ 1 ] - intersectPoint[ 1 ],
							lightPos[ 2 ] - intersectPoint[ 2 ],
							1.0
					);
					lightVec = matrixvecmath.normalize( lightVec );
					float skalarNL = sphereNormal[ 0 ] * lightVec[ 0 ] + sphereNormal[ 1 ] * lightVec[ 1 ] + sphereNormal[ 2 ] * lightVec[ 2 ];
					glm::vec4 reflectVec(
							2 * skalarNL * sphereNormal[ 0 ] - lightVec[ 0 ],
							2 * skalarNL * sphereNormal[ 1 ] - lightVec[ 1 ],
							2 * skalarNL * sphereNormal[ 2 ] - lightVec[ 2 ],
							1.0
					);
					reflectVec = matrixvecmath.normalize( reflectVec );
					float skalarRV = reflectVec[ 0 ] * view[ 0 ] + reflectVec[ 1 ] * view[ 1 ] + reflectVec[ 2 ] * view[ 2 ];

					phong_kd = phongDiffuse( phong, colorSurface, skalarNL );
					phong_ks = phongSpecular( phong, skalarRV );
					phongPixel += phong_kd + phong_ks;
				}

				//cout << endl << "skalarNL: " << skalarNL << " normal: " << glm::to_string( sphereNormal ) << " light: " << glm::to_string( lightVec ) << endl;
				//cout << "ka: " << glm::to_string( phong_ka ) << " kd: " << glm::to_string( phong_kd ) << " ks: " << glm::to_string( phong_ks ) << " sum: " << glm::to_string( phongPixel ) << endl;

				glm::vec3 pixelCol(
					abs( phongPixel[ 0 ] ) * 255,
					abs( phongPixel[ 1 ] ) * 255,
					abs( phongPixel[ 2 ] ) * 255
				);
				//cout << to_string( pixelCol ) << endl;


				//SAVE JUST COLOR
				//const string pixelColor = intersectColor.at( indexSmallest );
				//contentImgPlane.at( i ).push_back( pixelColor );

				//SAVE PHONG + COLOR
				stringstream sstr;
				sstr << int ( pixelCol[ 0 ] ) << " " << int ( pixelCol[ 1 ] ) << " " << int ( pixelCol[ 2 ] ) << "    ";
				string colorPixel = sstr.str();
				contentImgPlane.at( i ).push_back( colorPixel );
    			/*
				//SAVE NORMAL
				stringstream sstr;
				sstr << int ( abs( sphereNormal[ 0 ] * 255 ) ) << " " << int ( abs( sphereNormal[ 1 ] * 255 ) ) << " " << int ( abs( sphereNormal[ 2 ] * 255 ) ) << "    ";
				string colorPixel = sstr.str();
				contentImgPlane.at( i ).push_back( colorPixel );
				*/
			//2.b no intersection --> bgcolor
			}else{
		    	contentImgPlane.at( i ).push_back( "0 0 0   " );
	    		//cout << ray.posToColorString();
	    		//contentImgPlane.at( i ).push_back( ray.posToColorString() + "  " );
			}

	    }
    	contentImgPlane.at( i ).push_back( "\n" ); // Add column to every row
	}

	cout << "Ray tracing was successfull!" << endl;
}


glm::vec3 World::phongAmbient( glm::vec4 phong, glm::vec3 colorSurface ){
	glm::vec3 res(
		phong[ 0 ] * ambientLight[ 0 ] * colorSurface[ 0 ],
		phong[ 0 ] * ambientLight[ 1 ] * colorSurface[ 1 ],
		phong[ 0 ] * ambientLight[ 2 ] * colorSurface[ 2 ]
	);
	return res;
}

glm::vec3 World::phongDiffuse( glm::vec4 phong, glm::vec3 colorSurface, float skalarNL ){
	glm::vec3 res(
		phong[ 1 ] * parallelLightCol[ 0 ] * skalarNL * colorSurface[ 0 ],
		phong[ 1 ] * parallelLightCol[ 1 ] * skalarNL * colorSurface[ 1 ],
		phong[ 1 ] * parallelLightCol[ 2 ] * skalarNL * colorSurface[ 2 ]
	);
	if( res[ 0 ] < 0 ) res[ 0 ] = 0;
	if( res[ 1 ] < 0 ) res[ 1 ] = 0;
	if( res[ 2 ] < 0 ) res[ 2 ] = 0;
	return res;
}

glm::vec3 World::phongSpecular( glm::vec4 phong, float skalarRV ){
	if( skalarRV > 0 ){
		double pi = 3.1415926535897;
		glm::vec3 res(
			phong[ 2 ] * parallelLightCol[ 0 ] * ( ( phong[ 3 ] + 2 ) / 2 * pi ) * pow( skalarRV, phong[ 3 ] ),
			phong[ 2 ] * parallelLightCol[ 1 ] * ( ( phong[ 3 ] + 2 ) / 2 * pi ) * pow( skalarRV, phong[ 3 ] ),
			phong[ 2 ] * parallelLightCol[ 2 ] * ( ( phong[ 3 ] + 2 ) / 2 * pi ) * pow( skalarRV, phong[ 3 ] )
		);
		return res;
	}else{
		return glm::vec3( 0, 0, 0 );
	}

}
