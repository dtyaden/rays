#include <iostream>
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "math.h"
#include "triangle.h"
#include "camera.h"
#include "ray.h"
#include "rayhit.h"
#include "vec3.h"
#include "sphere.h"

using namespace std;

int height, width;
Camera* camera;
std::vector<Geom*> scene;
std::vector<Triangle*> triangles;
std::vector<Sphere*> spheres;

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
	Vec3 v = Vec3::subtract(pixel, position);
	v = Vec3::normalize(v);
	Ray r = Ray(v, pixel);
	return r;
}

float getTSphere(Vec3 center, Vec3 pixel, Vec3 vector, float radius){
	Vec3 c = center;
	Vec3 d = vector;
	Vec3 e = pixel;
	Vec3 emc = Vec3::subtract(c, e);
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

	float tValue = -(F*((A*K)-(J*B))+E*((J*C)-(A*L)) + D*((B*L)-(K*C)))/M;
	if(t<0)//no hit
		return -1;

	float Gamma = (I*((A*K)-(J*B)) + H*((J*C)-(A*L)) + G*((B*L)-(K*C)))/M;
	if(Gamma < 0 || Gamma > 1)
		return -1;

	float Beta = (J*((E*I)-(H*F)) + K*((G*F)-(D*I)) + L*((D*H)-(E*G)))/M;
	if(Beta < 0 || Beta > 1-Gamma)
		return -1;
	return tValue;
	

}

//start = point of intersection, v = unit vector to light
float diffuseIntersections(Vec3 start, Vec3 v, Vec3* normal){
	float diffuse = Vec3::dot(v, *normal);
	//diffuse = fabs(diffuse);
	diffuse = diffuse*1/2 + .5;
	cout << diffuse << "\n";
	return diffuse;

}
//start = point of intersection, v = unit vector to light
float shadow(Vec3 start, Vec3 v){
	Geom* closest = NULL;
	float value = 1;
	float t = 999;

	for(int j = 0; j < triangles.size();j++){
					Rayhit* r = triangles.at(j)->intersect(start, v, triangles.at(j));
				
				if(r->isNull);
				else if(r->time < t){
					t = r->time;
					closest = triangles.at(j);
					}
				}
				for(int j = 0; j < spheres.size();j++){
					Rayhit* r = spheres.at(j)->intersect(start, v, spheres.at(j));
				
				if(r->isNull);
				else if(r->time < t){
					t = r->time;
					cout<<"hit..."<<"\n";
					closest = spheres.at(j);
					}
				}
				if(closest == NULL)
					return value;
				else return .2;
}

void addTriangle(Vec3 a, Vec3 b, Vec3 c, Vec3 color){
	Triangle * tri = new Triangle(a,b,c, color);
	triangles.push_back(tri);
	scene.push_back(tri);
}

void addSphere(float radius, Vec3 position, Vec3 color){
	Sphere* sp =  new Sphere(radius,position, color);
	spheres.push_back(sp);
	scene.push_back(sp);
}

int main(int argc, char *argv[]){
	height = 512;
	width = 512;
	float distanceToCamera = 2;
	unsigned char colorR;
	unsigned char colorG;
	unsigned char colorB;
	Vec3 light(3,5,-15);
	camera = new Camera(Vec3(0,0,0), distanceToCamera, (float) width, (float) width);
	camera->test();
	Vec3 x(-6,-2,-30);
	Vec3 y(8,-2,-30);
	Vec3 z(8,10,-30);
	Triangle * tri = new Triangle(x,y,z, Vec3(1,0,1));
	triangles.push_back(tri);
	scene.push_back(tri);
	x = Vec3(-6,-2,-30);
	y = Vec3(8,10,-30);
	z = Vec3(-6, 10, -30);
	addTriangle(x,y,z, Vec3(1,0,1));

	x = Vec3(8,10,-30);
	y = Vec3(8,-2,-30);
	z = Vec3(8,-2,-15);
	addTriangle(x,y,z,Vec3(1,0,0));
	Sphere * sp =  new Sphere(1,Vec3(-4,0,-10), Vec3(1,0,0));
	//spheres.push_back(sp);
	//scene.push_back(sp); //Radius? pos, color
	sp =  new Sphere(1,Vec3(-2,0,-10), Vec3(1,0,0));
	//spheres.push_back(sp);
	//scene.push_back(sp);
	addSphere(2, Vec3(0,0,-16), Vec3(1,0,0));
	addSphere(1,Vec3(-2,-3,-10), Vec3(1,0,0));
	//spheres.push_back(sp);
	//scene.push_back(sp);
	unsigned int imagePixels = height*width;
	unsigned char image[height*width*3];//red,green,blue
	unsigned int imagePointer = 0;
	//makeImage(image, imagePixels);

	float smahBoat[2];
	for(int x = 0; x < width; x++){//row
		for(int y = 0; y < height; y++){//column
			smahBoat[0] = (float) ((x*2.0)/height)-1.0 ;
			smahBoat[1] = (float) ((y*2.0)/width)*-1+1.0;
			
			getRay(camera->position, Vec3(smahBoat[1], smahBoat[0], -distanceToCamera)); 
			Vec3 pixel(smahBoat[1]*-1,smahBoat[0]*-1,-distanceToCamera);
			//cout<<pixel.x<<" "<<pixel.y<<" "<<pixel.z<<"\n";
			//Vector from Pixel to Camera (GetRay?)
			Vec3 v = Vec3::subtract(camera->position ,pixel);
			//cout<< v.x<< " " << v.y<< " " <<v.z<< "\n";
			
			//Normalize Vector : Pixel to Camera
			v = Vec3::normalize(v);//ray
			float t = 999;
			Geom* closest = NULL;
			Rayhit* hit = NULL;
			Vec3* normal;
				for(int j = 0; j < triangles.size();j++){
					Rayhit* r = triangles.at(j)->intersect(pixel, v, triangles.at(j));
				
				if(r->isNull);
				else if(r->time < t){
					t = r->time;
					Triangle* temp = triangles.at(j);
					closest = temp;
					hit = r;
					//calculate normal for triangle
					Vec3 p1 = Vec3::subtract(temp->a, temp->b);
					Vec3 p2 = Vec3::subtract(temp->a, temp->c);
					normal = new Vec3(Vec3::normalize(Vec3::cross(p1,p2)));
					}
				}
				for(int j = 0; j < spheres.size();j++){
					Rayhit* r = spheres.at(j)->intersect(pixel, v, spheres.at(j));
				
				if(r->isNull);
				else if(r->time < t){
					t = r->time;
					closest = spheres.at(j);
					hit = r;
					//calculate normal for the sphere
					normal = new Vec3(Vec3::normalize(Vec3::subtract(spheres.at(j)->position, hit->position)));
					}
				}

			if(closest == NULL){
				colorR = 0;
				colorG = 0;
				colorB = 0;
			}
			else{
				float value = diffuseIntersections(hit->position, Vec3::normalize(Vec3::subtract(hit->position, light)), normal);
				//cout<<tri->color.x<<"\n";
				//cout<<closest->color.x<<"\n";
				colorR = closest->color.x*255 * value;
				colorG = closest->color.y*255 * value;
				colorB = closest->color.z*255 * value;
			}

			image[imagePointer++] = colorR;
			image[imagePointer++] = colorG;
			image[imagePointer++] = colorB;
			//cout << v.x<<" "<<v.y << " " << v.z <<"\n";
		}
	} 
	
	cout << stbi_write_png("dummy.png", width,height,3,image,width*3) << "\n";
	cout << "dumb\n";
}


