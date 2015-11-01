#ifndef TRIANGLE
#define TRIANGLE
#include "ray.h"
#include "rayhit.h"
#include "geom.h"
#include "vec3.h"

class Triangle : public Geom {
	
	public:
		Vec3 a, b, c;
		Vec3 color;
		Rayhit* intersect(Ray);
		Triangle () {};
		Triangle (Vec3 x, Vec3 y, Vec3 z, Vec3 color) : a(x), b(y), c(z),color(color) {};

};

#endif