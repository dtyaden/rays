#ifndef CAMERA
#define CAMERA
#include "vec3.h"
#include <iostream>
class Camera{
	
	public:
	Vec3 position;
	float distanceToScreen;
	float screenWidth;
	float screenHeight;
	float pixelWidth;
	float pixelHeight;
	Camera(Vec3, float,float,float);//use for square screen

};

#endif
