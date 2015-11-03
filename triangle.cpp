#include "triangle.h"


Rayhit* Triangle::intersect(Vec3 pixel, Vec3 vector, Triangle* t){

	
	float A = t->a.x - t->b.x;
	float B = t->a.y - t->b.y;
	float C = t->a.z - t->b.z;
	float D = t->a.x - t->c.x;
	float E = t->a.y - t->c.y;
	float F = t->a.z - t->c.z;
	float G = vector.x;
	float H = vector.y;
	float I = vector.z;
	float J = t->a.x - pixel.x;
	float K = t->a.y - pixel.y;
	float L = t->a.z - pixel.z;


	float M = (A*((E*I)-(H*F))) + (B*((G*F)-(D*I)))+(C*((D*H)-(E*G)));

	float tValue = -(F*((A*K)-(J*B))+E*((J*C)-(A*L)) + D*((B*L)-(K*C)))/M;
	if(tValue<=0){//no hit
		Rayhit * r = new Rayhit();
		r->isNull = 1;
		return r;
	}

	float Gamma = (I*((A*K)-(J*B)) + H*((J*C)-(A*L)) + G*((B*L)-(K*C)))/M;
	if(Gamma < 0 || Gamma > 1){
		Rayhit * r = new Rayhit();
		r->isNull = 1;
		return r;
	}
	float Beta = (J*((E*I)-(H*F)) + K*((G*F)-(D*I)) + L*((D*H)-(E*G)))/M;
	
	if(Beta < 0 || Beta > 1-Gamma){
		Rayhit * r = new Rayhit();
		r->isNull = 1;
		return r;
	}
	//std::cout<<"triangle HIT!!!!!!\n";
	Rayhit* r = new Rayhit();
	r->direction = vector;
	r->position = Vec3::mul(tValue,vector);
	r->position = Vec3::add(pixel,r->position);
	r->time = tValue;
	return r;
}
