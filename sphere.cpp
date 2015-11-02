#include "sphere.h"


Rayhit* Sphere::intersect(Vec3 pixel, Vec3 vector, Geom* geom){
	
	Vec3 c = position;
	Vec3 d = vector;
	Vec3 e = pixel;
	Vec3 emc = Vec3::subtract(c,e);
	float ddotd = Vec3::dot(d, d); //d.d
	float p1 = -1 * Vec3::dot(emc, d); //-d.(e-c)
	float p2 = Vec3::dot(emc, d); //d.(e-c)
	p2 *= p2; //(d.(e-c))^2//discriminant left side
	float p3 = Vec3::dot(emc, emc); //(e-c).(e-c)
	p3 -= radius * radius; //-R^2
	p3 *= ddotd;//discriminant right side
	float p4 = p2 - p3;//discriminant
	if(p4 < 0){
		Rayhit * r = new Rayhit();
		r->isNull = 1;
		return r;
	}

	//std::cout<<"HIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	p4 = sqrt(p4);
	float plus = fmax(0.0f, (p1 + p4));
	float minus = fmax(0.0f, (p1 - p4)); 
	float t = fmin(plus, minus);

	Rayhit* r = new Rayhit();
	r->position = Vec3::mul(t, d);
	r->position = Vec3::add(e, r->position);
	r->time = t;
	return r;
}