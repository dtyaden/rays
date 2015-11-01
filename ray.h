#ifndef RAY
#define RAY

#include "vec3.h"

class Ray{
public:
	Vec3 start;
	Vec3 end;
	//static Ray getRay(Vec3 start, Vec3 end){return Ray(start, end);};
	Ray(){};
	Ray(Vec3 start, Vec3 end) : start(start), end(end){};
};

#endif
