#include "vec3.h"


Vec3 Vec3::add(Vec3 a, Vec3 b){

	return Vec3((a.x + b.x), (a.y+b.y), (a.z+b.z));
}

Vec3 Vec3::subtract(Vec3 start, Vec3 end){

	return Vec3((end.x - start.x), (end.y-start.x), (end.z-start.z));
}

Vec3 Vec3::normalize(Vec3 v){

	float length = sqrt (v.x*v.x + v.y*v.y + v.z*v.z);
	if (length < 0)
		return v;
	
	return Vec3(v.x/length,v.y/length,v.z/length);
}