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

Vec3 Vec3::negatize(Vec3 v){
	return Vec3(-v.x, -v.y, -v.z);
}

float Vec3::dot(Vec3 v, Vec3 d){
	return v.x * d.x + v.y *d.y + v.z * d.z;
}

Vec3 Vec3::cross(Vec3 a, Vec3 b){
	return Vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

Vec3 Vec3::reflect(Vec3 I, Vec3 N){
	float a = 2.0 * Vec3::dot(I, N);
	Vec3 b = Vec3::mul(a, N);
	Vec3 c = Vec3::subtract(I, b);
	return c;
}

Vec3 Vec3::mul(float num, Vec3 vec){
	return Vec3(num*vec.x, num*vec.y, num*vec.z);
}
