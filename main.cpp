#include <iostream>
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "geom.h"
#include "triangle.h"
#include "camera.h"
#include "ray.h"
#include "rayhit.h"
#include "vec3.h"
#include "sphere.h"
#include "math.h"

using namespace std;

int height, width;
Camera* camera;
std::vector<Geom*> scene;


void makeImage(unsigned char image[], unsigned int pixels){
	unsigned int position = 0;
	
	for(int i = 0; i < pixels;i++){
		image[position++] = 255;
		image[position++] = 255;
		image[position++] = 255;
		
		//cout<< "Row: " << i/width <<"\n";
	}
}

Ray getRay(Vec3 position, Vec3 pixel){
	Vec3 v = Vec3::subtract(position, pixel);
	v = Vec3::normalize(v);
	Ray r = Ray(v, pixel);
	return r;
}

int main(int argc, char *argv[]){
	height = 8;
	width = 8;
	float distanceToCamera = 2;

	camera = new Camera(Vec3(0,0,0), distanceToCamera, (float) width, (float) width);
	Vec3 x(0,0,0);
	Vec3 y(0,1,0);
	Vec3 z(1,0,0);
	scene.push_back(new Triangle(x,y,z, Vec3(255,0,0)));
	scene.push_back(new Sphere(4,Vec3(0,0,-3), Vec3(255,0,0))); //Radius? pos, color
	unsigned int imagePixels = height*width;
	unsigned char image[height*width*3];//red,green,blue
	//makeImage(image, imagePixels);

	float smahBoat[2];
	for(int x = 0; x < width; x++){//row
		for(int y = 0; y < height; y++){//column
			smahBoat[0] = (float) ((x*2.0)/height)-1.0 ;
			smahBoat[1] = (float) ((y*2.0)/width)*-1+1.0;
			
			getRay(camera->position, Vec3(smahBoat[0], smahBoat[1], -distanceToCamera)); 

			//Vector from Pixel to Camera (GetRay?)
			Vec3 v = Vec3::subtract(camera->position ,Vec3(smahBoat[0],smahBoat[1],-distanceToCamera));
			//cout<< v.x<< " " << v.y<< " " <<v.z<< "\n";
			cout<< smahBoat[0] << " " << smahBoat[1] << "\n";
			//Normalize Vector : Pixel to Camera
			v = Vec3::normalize(v);//ray
			Ray r(v, camera->position);
			//cout << v.x<<" "<<v.y << " " << v.z <<"\n";
		}
	} 
	
	cout << stbi_write_png("dummy.png", width,height,3,image,width*3) << "\n";
	cout << "dumb\n";
}



float getTSphere(Vec3 center, Vec3 pixel, Vec3 vector, float radius){
	Vec3 c = center;
	Vec3 d = vector;
	Vec3 e = pixel;
	Vec3 emc = Vec3::subtract(e, c);
	float ddotd = Vec3::dot(d, d); //d.d
	float p1 = -1 * Vec3::dot(emc, d); //-d.(e-c)
	float p2 = Vec3::dot(emc, d); //d.(e-c)
	p2 *= p2; //(d.(e-c))^2
	float p3 = Vec3::dot(emc, emc); //(e-c).(e-c)
	p3 -= radius * radius; //-R^2
	p3 *= ddotd;
	float p4 = p2 - p3;
	p4 = sqrt(p4);
	float plus = (p1 + p4) / ddotd;
	float minus = (p1 - p4) / ddotd; 
	return min(plus, minus);
}

float getTTriangle(Triangle* t, Vec3 pixel, Vec3 vector ){ //Pixel = start
	float A = t->a.x - t->b.x;
	float B = t->a.y - t->b.y;
	float C = t->a.z - t->b.z;
	float D = t->a.x - t->c.x;
	float E = t->a.y - t->c.y;
	float F = t->a.x - t->c.z;
	float G = pixel.x;
	float H = pixel.y;
	float I = pixel.z;
	float J = t->a.x - vector.x;
	float K = t->a.y - vector.y;
	float L = t->a.z - vector.z;

	float M = (A*((E*I)-(H*F))) + (B*((G*F)-(D*I)))+(C*((D*H)-(E*G)));

	float Beta = (J*((E*I)-(H*F)) + K*((G*F)-(D*I)) + L*((D*H)-(E*G)))/M;
	float Gamma = (I*((A*K)-(J*B)) + H*((J*C)-(A*L)) + G*((B*L)-(K*C)))/M;
	return -(F*((A*K)-(J*B))+E*((J*C)-(A*L)) + D*((B*L)-(K*C)))/M;
	

}
