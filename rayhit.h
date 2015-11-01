#ifndef RAYHIT
#define RAYHIT

#include "vec3.h"
#include "ray.h"

class Rayhit{
	public:
		int time;
		int shading;
		Vec3 location;
		Ray ray;

};

#endif