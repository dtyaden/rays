#ifndef VEC3
#define VEC3
#include <math.h>

class Vec3{
	
	public:
		float vector[3];
		float x,y,z;
		static Vec3 add(Vec3, Vec3);
		static Vec3 subtract(Vec3, Vec3);
		static Vec3 normalize(Vec3);
		Vec3(){};
		Vec3(float x, float y, float z) : x(x), y(y), z(z) {vector[0] = x; vector[1] = y, vector[2] = z;};


};

#endif