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
	//posImgPlaneTopLeft[ 0 ] += pixelWidth;
	posImgPlaneTopLeft[ 1 ] -= pixelHeight;


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
	meshes.push_back( mesh);
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

	for( unsigned int i = 0; i < meshes.size(); ++i ){
		meshes.at( i ).print();
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

	contentImgPlane.clear();
	for (int i = 0; i < heightImgPlane; i++) {
		contentImgPlane.push_back(vector<string>()); // Add one empty row
	}

	//FOR EVERY PIXEL
	for (unsigned int i = 0; i < contentImgPlane.size(); i++) {
	    for (int j = 0; j < widthImgPlane; j++) {

	    	//1. calculate direction of ray
	    	glm::vec4 posRayOnPlane = posImgPlaneTopLeft;
			posRayOnPlane[ 0 ] = posRayOnPlane[ 0 ] + j * rightVec[ 0 ] * pixelWidth - i * (upCamera[ 0 ]) * pixelHeight;
			posRayOnPlane[ 1 ] = posRayOnPlane[ 1 ] + j * rightVec[ 1 ] * pixelWidth - i * (upCamera[ 1 ]) * pixelHeight;
			posRayOnPlane[ 2 ] = posRayOnPlane[ 2 ] + j * rightVec[ 2 ] * pixelWidth - i * (upCamera[ 2 ]) * pixelHeight;
	    	glm::vec4 ray(
	    			posRayOnPlane[ 0 ] - posCamera[ 0 ],
					posRayOnPlane[ 1 ] - posCamera[ 1 ],
					posRayOnPlane[ 2 ] - posCamera[ 2 ],
					1.0 );
			//cout << "i: " << i << " j: " << j << endl;
	    	//cout << ray.toString() << endl;
			ray = matrixvecmath.normalize( ray );

			//2. trace ray
			glm::vec3 pixelCol = traceRay( ray, 0 );

			if( pixelCol[ 0 ] > 255 ) pixelCol[ 0 ] = 255;
			if( pixelCol[ 1 ] > 255 ) pixelCol[ 1 ] = 255;
			if( pixelCol[ 2 ] > 255 ) pixelCol[ 2 ] = 255;

	    	//3. save results to imgPlane
			stringstream sstr;
			sstr << int ( pixelCol[ 0 ] * 255 ) << " " << int ( pixelCol[ 1 ] * 255 ) << " " << int ( pixelCol[ 2 ] * 255 ) << "    ";
			string colorPixel = sstr.str();
			contentImgPlane.at( i ).push_back( colorPixel );

	    }
    	contentImgPlane.at( i ).push_back( "\n" ); // Add column to every row
	}

	cout << "Ray tracing was successfull!" << endl;
}

glm::vec3 World::phongShading( glm::vec4 phong, glm::vec3 colorSurface, glm::vec3 intersectPoint, glm::vec4 normalVec ){
	Matrix_vec_math matrixvecmath;

	glm::vec3 phong_ka = phongAmbient( phong, colorSurface );
	glm::vec3 phong_kd( 0.0, 0.0, 0.0 );
	glm::vec3 phong_ks( 0.0, 0.0, 0.0 );

	glm::vec3 phongPixel = phong_ka; //the sum of all shading therms



	glm::vec4 view = matrixvecmath.vec3ToVec4( matrixvecmath.vec4ToVec3( posCamera ) - intersectPoint );
	view = matrixvecmath.normalize( view );

	//phong_kd, phong_ks for parallel light
	if( parallelLightDir[ 0 ] != 0 || parallelLightDir[ 1 ] != 0 || parallelLightDir[ 2 ] != 0 ){
		glm::vec4 lightVec( -parallelLightDir[ 0 ], -parallelLightDir[ 1 ], -parallelLightDir[ 2 ], 1.0 );
		lightVec = matrixvecmath.normalize( lightVec );
		float skalarNL = normalVec[ 0 ] * lightVec[ 0 ] + normalVec[ 1 ] * lightVec[ 1 ] + normalVec[ 2 ] * lightVec[ 2 ];
		glm::vec4 reflectVec(
				2 * skalarNL * normalVec[ 0 ] - lightVec[ 0 ],
				2 * skalarNL * normalVec[ 1 ] - lightVec[ 1 ],
				2 * skalarNL * normalVec[ 2 ] - lightVec[ 2 ],
				1.0
		);
		reflectVec = matrixvecmath.normalize( reflectVec );
		float skalarRV = reflectVec[ 0 ] * view[ 0 ] + reflectVec[ 1 ] * view[ 1 ] + reflectVec[ 2 ] * view[ 2 ];

		phong_kd = phongDiffuse( phong, colorSurface, parallelLightCol, skalarNL );
		phong_ks = phongSpecular( phong, skalarRV, parallelLightCol );
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
		float skalarNL = normalVec[ 0 ] * lightVec[ 0 ] + normalVec[ 1 ] * lightVec[ 1 ] + normalVec[ 2 ] * lightVec[ 2 ];
		glm::vec4 reflectVec(
				2 * skalarNL * normalVec[ 0 ] - lightVec[ 0 ],
				2 * skalarNL * normalVec[ 1 ] - lightVec[ 1 ],
				2 * skalarNL * normalVec[ 2 ] - lightVec[ 2 ],
				1.0
		);
		reflectVec = matrixvecmath.normalize( reflectVec );
		float skalarRV = reflectVec[ 0 ] * view[ 0 ] + reflectVec[ 1 ] * view[ 1 ] + reflectVec[ 2 ] * view[ 2 ];

		phong_kd = phongDiffuse( phong, colorSurface, pointLightsCol.at( i ), skalarNL );
		phong_ks = phongSpecular( phong, skalarRV, pointLightsCol.at( i ) );
		phongPixel += phong_kd + phong_ks;


	}

	if ( phongPixel[ 0 ] > 1 ) phongPixel[ 0 ] = 1;
	if ( phongPixel[ 1 ] > 1 ) phongPixel[ 1 ] = 1;
	if ( phongPixel[ 2 ] > 1 ) phongPixel[ 2 ] = 1;

	//cout << endl << "skalarNL: " << skalarNL << " normal: " << glm::to_string( sphereNormal ) << " light: " << glm::to_string( lightVec ) << endl;
	//cout << "ka: " << glm::to_string( phong_ka ) << " kd: " << glm::to_string( phong_kd ) << " ks: " << glm::to_string( phong_ks ) << " sum: " << glm::to_string( phongPixel ) << endl;

	glm::vec3 pixelCol(
		( phongPixel[ 0 ] ) * 255,
		( phongPixel[ 1 ] ) * 255,
		( phongPixel[ 2 ] ) * 255
	);
	//cout << to_string( pixelCol ) << endl;

	return pixelCol;
}


glm::vec3 World::phongAmbient( glm::vec4 phong, glm::vec3 colorSurface ){
	glm::vec3 res(
		phong[ 0 ] * ambientLight[ 0 ] * colorSurface[ 0 ],
		phong[ 0 ] * ambientLight[ 1 ] * colorSurface[ 1 ],
		phong[ 0 ] * ambientLight[ 2 ] * colorSurface[ 2 ]
	);
	return res;
}

glm::vec3 World::phongDiffuse( glm::vec4 phong, glm::vec3 colorSurface, glm::vec3 lightColor, float skalarNL ){
	glm::vec3 res(
		phong[ 1 ] * lightColor[ 0 ] * skalarNL * colorSurface[ 0 ],
		phong[ 1 ] * lightColor[ 1 ] * skalarNL * colorSurface[ 1 ],
		phong[ 1 ] * lightColor[ 2 ] * skalarNL * colorSurface[ 2 ]
	);
	if( res[ 0 ] < 0 ) res[ 0 ] = 0;
	if( res[ 1 ] < 0 ) res[ 1 ] = 0;
	if( res[ 2 ] < 0 ) res[ 2 ] = 0;
	return res;
}

glm::vec3 World::phongSpecular( glm::vec4 phong, float skalarRV, glm::vec3 lightColor ){
	if( skalarRV > 0 ){
		glm::vec3 res(
			phong[ 2 ] * lightColor[ 0 ] * pow( skalarRV, phong[ 3 ] ),
			phong[ 2 ] * lightColor[ 1 ] * pow( skalarRV, phong[ 3 ] ),
			phong[ 2 ] * lightColor[ 2 ] * pow( skalarRV, phong[ 3 ] )
		);
		return res;
	}else{
		return glm::vec3( 0, 0, 0 );
	}

}

string World::posRayToString( glm::vec4 ray ){
	stringstream sstrX, sstrY, sstrZ;
	float x, y, z;
	x = ray[ 0 ] * 100;
	y = ray[ 1 ] * 100;
	z = ray[ 2 ] >= 0 ? ray[ 2 ] : 0;
	sstrX << abs(int(x));
	string posX = sstrX.str();
	sstrY << abs(int(y));
	string posY = sstrY.str();
	sstrZ << abs(int(z));
	string posZ = sstrZ.str();
	//cout << x << " " << direction[ 0 ] << " " << abs(int(x))<< endl;
	return posX + " " + posY + " " + posZ;
}

glm::vec3 World::traceRay( glm::vec4 ray, int bounces ){
	Matrix_vec_math matrixvecmath;

	if( bounces < maxBounces ) {

		float reflection = 0.0;

		//1. perform intersection test ray-sphere
		vector< float > lambdaSpheres;
		vector< Sphere > intersectedSpheres;
		for( unsigned int i = 0; i < spheres.size(); ++i ){
			glm::vec4 posSphere( spheres.at( i ).get_position() );
			float radiusSphere = spheres.at( i ).get_radius();
			float a =  ray[ 0 ] * ray[ 0 ] +
					   ray[ 1 ] * ray[ 1 ] +
					   ray[ 2 ] * ray[ 2 ];

			float b =  ( 2 * posCamera[ 0 ] * ray[ 0 ] - 2 * posSphere[ 0 ] * ray[ 0 ] ) +
					   ( 2 * posCamera[ 1 ] * ray[ 1 ] - 2 * posSphere[ 1 ] * ray[ 1 ] ) +
					   ( 2 * posCamera[ 2 ] * ray[ 2 ] - 2 * posSphere[ 2 ] * ray[ 2 ] );

			float c = pow ( posCamera[ 0 ] - posSphere[ 0 ], 2 ) +
					  pow ( posCamera[ 1 ] - posSphere[ 1 ], 2 ) +
					  pow ( posCamera[ 2 ] - posSphere[ 2 ], 2 ) -
					  pow ( radiusSphere, 2 );
			float intersection = pow( b, 2 ) - 4 * a * c;
			if( intersection >= 0 ){
				float lambdaOne = ( -b + sqrt( intersection ) ) / 2 * a;
				float lambdaTwo = ( -b - sqrt( intersection ) ) / 2 * a;
				if( lambdaOne <= lambdaTwo ) lambdaSpheres.push_back( lambdaOne );
				if( lambdaOne > lambdaTwo ) lambdaSpheres.push_back( lambdaTwo );

				intersectedSpheres.push_back( spheres.at( i ) );
			}
		}

		/*
		cout << "INTERSECTIONS: " << endl;
		for( unsigned int i = 0; i < lambdaSpheres.size(); ++i ){
			cout << lambdaSpheres.at( i ) << endl;
		}
		*/

		//2. perform intersection test ray-triangle
		vector< float > lambdaTriangles;
		vector< Mesh > intersectedMeshes;
		vector< glm::vec3 > posTriangles;
		glm::vec3 normalTri;
		for( unsigned int iTri = 0; iTri < meshes.size(); ++iTri ){
			std::vector < Triangle > triangles = meshes.at( iTri ).get_triangles();
			unsigned int jTri = 0;
			for( ; jTri < triangles.size(); ++jTri ){
				//if( j > 0 ) cout << "BINGO" << endl;
				glm::vec3 barycentricPos;

				glm::vec3 p = glm::cross( matrixvecmath.vec4ToVec3( ray ), triangles.at( jTri ).get_e2() );
				float a = glm::dot( triangles.at( jTri ).get_e1(), p );
				if( a >= 0 ){

					float f = 1.0 / a;
					glm::vec3 s = matrixvecmath.vec4ToVec3( posCamera ) - triangles.at( jTri ).get_v().at( 0 );

					barycentricPos[ 0 ] = f * glm::dot( s, p );
					if( barycentricPos[ 0 ] >= 0.0 && barycentricPos[ 0 ] <= 1.0 ){

						glm::vec3 q = glm::cross( s, triangles.at( jTri ).get_e1() );
						barycentricPos[ 1 ] = f * glm::dot( matrixvecmath.vec4ToVec3( ray ), q );
	/*					if( i == 355 && j == 240 ){
							barycentricPos[ 0 ] = 0.5;
							barycentricPos[ 1 ] = 0.1;
						}*/
						if( barycentricPos[ 1 ] >= 0.0 && ( barycentricPos[ 0 ] + barycentricPos[ 1 ] ) <= 1.0 ){

							barycentricPos[ 2 ] = f * glm::dot( triangles.at( jTri ).get_e2(), q );
							if( barycentricPos[ 2 ] >= 0 ){
								//if( barycentricPos[ 0 ] == barycentricPos[ 1 ] ) cout << barycentricPos[ 1 ] << " " << barycentricPos[ 1 ] << endl;

								lambdaTriangles.push_back( barycentricPos[ 2 ] );
								intersectedMeshes.push_back( meshes.at( iTri ) );
								posTriangles.push_back( barycentricPos );
								normalTri = triangles.at( jTri ).get_n();
							}

						}

					}
				}

			}
		}

		//3. there is an intersection
		if( lambdaSpheres.size() != 0 || lambdaTriangles.size() != 0){

			//4.a. find smallest lambda spheres
			int indexSmallest = 0;
			for( unsigned int i = 0; i < lambdaSpheres.size(); ++i ){
				float* smallest = &lambdaSpheres.at( i );
				for( unsigned int j = 1; j < lambdaSpheres.size() - i; ++j ){
					float* smaller = &lambdaSpheres.at( i + j );
					if( *smallest > *smaller ){
						indexSmallest = j;
						//float temp = *smaller;
						//*smaller = *biggest;
						*smallest = *smaller;
					}
				}
			}

			//4.b. find smallest lambda triangles
			int indexSmallestTri = 0;
			for( unsigned int i = 0; i < lambdaTriangles.size(); ++i ){
				float* smallest = &lambdaTriangles.at( i );
				for( unsigned int j = 1; j < lambdaTriangles.size() - i; ++j ){
					float* smaller = &lambdaTriangles.at( i + j );
					if( *smallest > *smaller ){
						indexSmallestTri = j;
						//float temp = *smaller;
						//*smaller = *biggest;
						*smallest = *smaller;
					}
				}
			}

			//4.c. check if sphere or triangle is in the front
			string intersectedObjType;
			if( lambdaSpheres.size() != 0 ) intersectedObjType = "sphere";
			if( lambdaTriangles.size() != 0 ) intersectedObjType = "triangle";
			if( lambdaSpheres.size() != 0 && lambdaTriangles.size() != 0){
				if( lambdaSpheres.at( indexSmallest ) <= lambdaTriangles.at( indexSmallestTri ) ) intersectedObjType = "sphere";
				if( lambdaSpheres.at( indexSmallest ) > lambdaTriangles.at( indexSmallestTri ) ) intersectedObjType = "triangle";
			}

			//5. phong shading
			glm::vec3 pixelCol;
			glm::vec4 sphereNormal;

			//5.a calculate phong shading for sphere
			if( intersectedObjType == "sphere" ){
				glm::vec4 phong = intersectedSpheres.at( indexSmallest ).get_phong();
				glm::vec3 colorSurface = intersectedSpheres.at( indexSmallest ).get_color();

				glm::vec3 intersectPoint(
						posCamera[ 0 ] + lambdaSpheres.at( indexSmallest ) * ray[ 0 ],
						posCamera[ 1 ] + lambdaSpheres.at( indexSmallest ) * ray[ 1 ],
						posCamera[ 2 ] + lambdaSpheres.at( indexSmallest ) * ray[ 2 ]
				);

				sphereNormal =  matrixvecmath.vec3ToVec4( intersectPoint - matrixvecmath.vec4ToVec3( intersectedSpheres.at( indexSmallest ).get_position() ) / intersectedSpheres.at( indexSmallest ).get_radius() );
				sphereNormal = matrixvecmath.normalize( sphereNormal );

				pixelCol = phongShading( phong, colorSurface, intersectPoint, sphereNormal );

				reflection = intersectedSpheres.at( indexSmallest ).get_reflectance();
				if( reflection != 0.0 ){
					glm::vec4 reflRay(
							ray[ 0 ] - 2 * ( glm::dot( ray[ 0 ], sphereNormal[ 0 ] ) * sphereNormal[ 0 ] ),
							ray[ 1 ] - 2 * ( glm::dot( ray[ 1 ], sphereNormal[ 1 ] ) * sphereNormal[ 1 ] ),
							ray[ 2 ] - 2 * ( glm::dot( ray[ 2 ], sphereNormal[ 2 ] ) * sphereNormal[ 2 ] ),
							1.0
					);
					++bounces;
					pixelCol = ( 1 - reflection) * pixelCol + reflection * traceRay( reflRay, bounces );
				}
			}

			//5.b. calculate phong shading for triangle
			if( intersectedObjType == "triangle" ){
				glm::vec4 phong = intersectedMeshes.at( indexSmallestTri ).get_phong();
				glm::vec3 colorSurface = intersectedMeshes.at( indexSmallestTri ).get_color();

				glm::vec3 intersectPoint(
						posCamera[ 0 ] + lambdaTriangles.at( indexSmallest ) * ray[ 0 ],
						posCamera[ 1 ] + lambdaTriangles.at( indexSmallest ) * ray[ 1 ],
						posCamera[ 2 ] + lambdaTriangles.at( indexSmallest ) * ray[ 2 ]
				);

				pixelCol = phongShading( phong, colorSurface, intersectPoint, matrixvecmath.vec3ToVec4( normalTri ) );

				reflection = intersectedMeshes.at( indexSmallestTri ).get_reflectance();
				if( reflection != 0.0 ){
					glm::vec4 reflRay(
							ray[ 0 ] - 2 * ( glm::dot( ray[ 0 ], normalTri[ 0 ] ) * normalTri[ 0 ] ),
							ray[ 1 ] - 2 * ( glm::dot( ray[ 1 ], normalTri[ 1 ] ) * normalTri[ 1 ] ),
							ray[ 2 ] - 2 * ( glm::dot( ray[ 2 ], normalTri[ 2 ] ) * normalTri[ 2 ] ),
							1.0
					);
					++bounces;
					pixelCol = ( 1 - reflection) * pixelCol + reflection * traceRay( reflRay, bounces );
				}
			}

			//5.c save results from phong shading
			if( intersectedObjType == "sphere" || intersectedObjType == "triangle" ){

				//6.1 save color + phong
				//return pixelCol;

				//6.2 save normal
				sphereNormal[ 0 ] = abs( sphereNormal[ 0 ] );
				sphereNormal[ 1 ] = abs( sphereNormal[ 1 ] );
				sphereNormal[ 2 ] = abs( sphereNormal[ 2 ] );
				sphereNormal[ 3 ] = 1.0;
				return matrixvecmath.vec4ToVec3( sphereNormal );

			}
		}

		//3.b. no intersection --> bgcolor
		return bgcolor;
	}

	return bgcolor;
}
