#ifndef TRIANGLE
#define TRIANGLE
#include "ray.h"
#include "rayhit.h"
#include "vec3.h"
#include <cstddef>
#include <iostream>

class Triangle : public Geom {
	
	public:
		Vec3 a, b, c;
		Rayhit* intersect( Vec3 pixel, Vec3 vector, Triangle* t);
		Triangle () {};
		Triangle (Vec3 x, Vec3 y, Vec3 z, Vec3 color) : a(x), b(y), c(z) {this->color = color;};

};

#endif