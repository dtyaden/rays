#ifndef SPHERE
#define SPHERE
#include "ray.h"
#include "rayhit.h"
#include "vec3.h"
#include "math.h"
#include <cstddef>
#include <iostream>

class Sphere : public Geom{
	public:
		float radius;
		Vec3 position;
		Rayhit* intersect(Vec3 pixel, Vec3 vector, Geom* geom);
		Sphere(){};
		Sphere(float radius, Vec3 position, Vec3 color) : radius(radius), position(position){this->color = color;};
};

#endif