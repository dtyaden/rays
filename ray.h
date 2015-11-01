#ifndef RAY
#define RAY

#include "vec3.h"

class Ray{
public:
	Vec3 vector;
	Vec3 start;
	Ray(){};
	Ray(Vec3 vector, Vec3 start) : vector(vector), start(start){};
};

#endif