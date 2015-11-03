#ifndef RAYHIT
#define RAYHIT

#include "vec3.h"
#include "ray.h"

class Rayhit{
	public:
		float time;
		int isNull;
		int shading;
		Vec3 position;
		Vec3 direction;
		Ray ray;
		Rayhit(){isNull = 0;};
};

class Geom{

public:
	int reflective;
	Vec3 color;
	virtual Rayhit* intersect(Vec3, Vec3, Geom*){};
};

#endif