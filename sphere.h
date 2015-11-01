#ifndef SPHERE
#define SPHERE
#include "ray.h"
#include "rayhit.h"
#include "geom.h"
#include "vec3.h"

class Sphere : public Geom{
	public:
		float radius;
		Vec3 position;
		Vec3 color;
		Rayhit* intersect(Ray);
		Sphere(){};
		Sphere(float radius, Vec3 position, Vec3 color) : radius(radius), position(position), color(color){};
};

#endif