#ifndef GEOM
#define GEOM
#include "lib/vecmat.h"
#include "vec3.h"
#include "ray.h"
#include "rayhit.h"

class Geom{
public:
	int reflective;
	Vec3 color;
	virtual Rayhit* intersect(){};
};

#endif