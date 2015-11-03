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
#include "string.h"

using namespace std;

int height, width;
Camera* camera;
std::vector<Geom*> scene;
std::vector<Triangle*> triangles;
std::vector<Sphere*> spheres;
Vec3 light(3,5,-15);
int isSphere = 0;
int renderReflections = 1;
int mode = 0;
int skipShadows = 0;

//start = point of intersection, v = unit vector to light
float diffuseIntersections(Vec3 start, Vec3 v, Vec3* normal){
	float diffuse = Vec3::dot(v, *normal);

	//diffuse = fabs(diffuse);
	diffuse = diffuse*1/2 + .5;
	return diffuse;

}

float shadow(Rayhit* hit){
	if(skipShadows)//for fancy option
		return 1;
		
	//get unit vector to light
	Vec3 v(Vec3::normalize(Vec3::subtract(hit->position, light)));
	
	Vec3 start = hit->position;
	Geom* closest = NULL;
	
	float value = 1;
	float multiplier = (float) 1/100;//anti-self intersect
	float t = 999;

	start.x = v.x*multiplier + start.x;
	start.y = v.y*multiplier + start.y;
	start.z = v.z*multiplier + start.z;
	
	Rayhit* ray = new Rayhit();
	ray -> isNull = 1;
	
	//attempt to intersect every geom
	for(int j = 0; j < triangles.size();j++){
		Rayhit* r = triangles.at(j)->intersect(start, v, triangles.at(j));
		

		if(r->isNull);
		else if(r->time < t){
			float rayLen, lightDistance;
			rayLen = Vec3::length(Vec3::subtract(start, r->position));
			lightDistance = Vec3::length(Vec3::subtract(start, light));
			if (rayLen < lightDistance){ 
				t = r->time;
				closest = triangles.at(j);
				ray = r;
				}
			}
		}
	for(int j = 0; j < spheres.size();j++){
		Rayhit* r = spheres.at(j)->intersect(start, v, spheres.at(j));
			
		if(r->isNull);
		else if(r->time < t){
			float rayLen, lightDistance;
			rayLen = Vec3::length(Vec3::subtract(start, r->position));
			lightDistance = Vec3::length(Vec3::subtract(start, light));
			if(isSphere){
		}
			if(rayLen < lightDistance){
			t = r->time;
			closest = spheres.at(j);
			ray = r;
				}
			}
		}
		//if there is a hit in the intersections, return .2, otherwise return 1
		if(ray->isNull)
			return value;
		else return .2;
}

Vec3 reflection(Rayhit* hit, int n, Vec3* normal,Geom* intersectedGeom){
	Vec3 direction;
	Vec3 reflectionVector;
	float a;
	
	//calculate incident
	direction = Vec3::normalize(hit->direction);
	
	//calculate reflection vector
	a = 2*Vec3::dot(direction, *normal);
	reflectionVector = Vec3::subtract(Vec3::mul(a, *normal), direction);
	Vec3 start = hit->position;
	Geom* closest = NULL;
	float value = 1;
	float multiplier = (float) 1/100;//apply so geometry won't intersect itself
	float t = 999;
	
	start.x = reflectionVector.x*multiplier + start.x;
	start.y = reflectionVector.y*multiplier + start.y;
	start.z = reflectionVector.z*multiplier + start.z;
	Rayhit* ray = new Rayhit();
	ray -> isNull = 1;

	//attempt to intersect every geom
	for(int j = 0; j < triangles.size();j++){
		Rayhit* r = triangles.at(j)->intersect(start, reflectionVector, triangles.at(j));
		
		if(r->isNull);
		else if(r->time < t){
			Triangle* temp = triangles.at(j);
			closest = temp;				
			hit = r;
			isSphere = 0;
			//calculate normal for triangle
			Vec3 p1 = Vec3::subtract(temp->a, temp->b);
			Vec3 p2 = Vec3::subtract(temp->a, temp->c);
			normal = new Vec3(Vec3::normalize(Vec3::cross(p1,p2)));
			ray = r;
			}
		}
	for(int j = 0; j < spheres.size();j++){
		Rayhit* r = spheres.at(j)->intersect(start, reflectionVector, spheres.at(j));
		if(r->isNull);
		else if(r->time < t){
			t = r->time;
			normal = new Vec3(Vec3::normalize(Vec3::subtract(spheres.at(j)->position, r->position)));
			closest = spheres.at(j);
			ray = r;
			}
		}

		if(ray->isNull || n == 10){
			
			return Vec3(0,0,0);//return black after ten bounces/no hit
		}
		else if(closest->reflective){
			return reflection(ray, ++n, normal, closest);
		}
		else{
			//calculate shadow and diffuse for objects in reflection
			Vec3 hitToLight = Vec3::normalize(Vec3::subtract(ray->position, light));
			float inShadow = 1;
			inShadow = shadow(ray);
			float diffuse;
			diffuse = diffuseIntersections(ray->position, Vec3::normalize(hitToLight), normal);
			Vec3 newColor(Vec3::mul(diffuse,(Vec3::mul(inShadow,closest->color))));
			
			
			return newColor;
		}

}

//helper to build scene
void addTriangle(Vec3 a, Vec3 b, Vec3 c, Vec3 color, int reflective){
	Triangle * tri = new Triangle(a,b,c, color);
	tri->reflective = reflective;
	triangles.push_back(tri);
	scene.push_back(tri);
}

//helper to build scene
void addSphere(float radius, Vec3 position, Vec3 color, int reflective){
	Sphere* sp =  new Sphere(radius,position, color);
	sp->reflective = reflective;
	spheres.push_back(sp);
	scene.push_back(sp);
}


//creates a well known character
void buildFancy(){
	light = Vec3(0,0, -10);
	
	skipShadows = 1;
	Vec3 x(-4.5,0,-14);
	Vec3 y(-2,-1.5,-14);
	Vec3 z(-2,1.5,-14);
	addTriangle(x,y,z, Vec3(0,0,0),0);
	
	x = Vec3(-20,6,-14);
	y = Vec3(-20,3,-14);
	z = Vec3(20,6,-14);
	addTriangle(x,y,z, Vec3(0,0,.8),0);
	x = Vec3(-20,3,-14);
	y = Vec3(20,3,-14);
	z = Vec3(20,6,-14);
	addTriangle(x,y,z, Vec3(0,0,.8),0);
	
	x = Vec3(-20,-6,-14);
	y = Vec3(-20,-3,-14);
	z = Vec3(20,-6,-14);
	addTriangle(x,y,z, Vec3(0,0,.8),0);
	x = Vec3(-20,-3,-14);
	y = Vec3(20,-3,-14);
	z = Vec3(20,-6,-14);
	addTriangle(x,y,z, Vec3(0,0,.8),0);
	
	
	addSphere(2,Vec3(-5,0,-16),Vec3(1,1,0),0);
	addSphere(1,Vec3(-1,0,-16),Vec3(1,1,1),0);
	addSphere(1,Vec3(3,0,-16),Vec3(1,1,1),0);
	addSphere(1,Vec3(6.5,0,-16),Vec3(1,1,1),0);
}

//turn walls into mirrors, move light source, move reflective
//right sphere up, make big sphere solid blue
void buildCustom(){
	
	light = Vec3(-3,5,-13);
	Vec3 x(-8,-2,-20);
	Vec3 y(8,-2,-20);
	Vec3 z(8,10,-20);
	addTriangle(x,y,z, Vec3(0,0,1),1);
	x = Vec3(-8,-2,-20);
	y = Vec3(8,10,-20);
	z = Vec3(-8, 10, -20);
	addTriangle(x,y,z, Vec3(0,0,1),1);
	
	//right side triangle
	x = Vec3(8,-2,-20);
	y = Vec3(8,-2,-10);
	z = Vec3(8,10,-20);
	addTriangle(x,y,z,Vec3(1,0,0),1);
	//floor
	x = Vec3(-8,-2,-20);
	y = Vec3(8,-2,-10);
	z = Vec3(8,-2,-20);
	addTriangle(x,y,z,Vec3(.8,.8,.8),1);
	x = Vec3(-8,-2,-20);
	y = Vec3(-8,-2,-10);
	z = Vec3(8,-2,-10);
	addTriangle(x,y,z,Vec3(.8,.8,.8),1);

	addSphere(1, Vec3(-3,-1,-14), Vec3(1,0,0),0);
	addSphere(1,Vec3(3,3,-14), Vec3(0,0,1),1);
	addSphere(2,Vec3(0,0,-16),Vec3(.2,0,.8),0);
}

void buildReference(){
	//back wall
	Vec3 x(-8,-2,-20);
	Vec3 y(8,-2,-20);
	Vec3 z(8,10,-20);
	addTriangle(x,y,z, Vec3(0,0,1),0);
	x = Vec3(-8,-2,-20);
	y = Vec3(8,10,-20);
	z = Vec3(-8, 10, -20);
	addTriangle(x,y,z, Vec3(0,0,1),0);
	
	//right side triangle
	x = Vec3(8,-2,-20);
	y = Vec3(8,-2,-10);
	z = Vec3(8,10,-20);
	addTriangle(x,y,z,Vec3(1,0,0),0);
	//floor
	x = Vec3(-8,-2,-20);
	y = Vec3(8,-2,-10);
	z = Vec3(8,-2,-20);
	addTriangle(x,y,z,Vec3(.8,.8,.8),0);
	x = Vec3(-8,-2,-20);
	y = Vec3(-8,-2,-10);
	z = Vec3(8,-2,-10);
	addTriangle(x,y,z,Vec3(.8,.8,.8),0);

	addSphere(1, Vec3(-3,-1,-14), Vec3(1,0,0),0);
	addSphere(1,Vec3(3,-1,-14), Vec3(0,0,1),1);
	addSphere(2,Vec3(0,0,-16),Vec3(0,0,0),1);
}

int main(int argc, char *argv[]){
	height = 512;
	width = 512;
	float distanceToCamera = 2;
	unsigned char colorR;
	unsigned char colorG;
	unsigned char colorB;
	camera = new Camera(Vec3(0,0,0), distanceToCamera, (float) width, (float) width);

	if(argc<2){
		cout<<"no argument specified, rendering to reference.png\n";
		buildReference();
	}else if(strcmp(argv[1],"custom") == 0){
		mode = 1;
		buildCustom();
	}
	else if(strcmp(argv[1], "fancy") ==0){
		mode = 2;
		buildFancy();
	}
	else buildReference();

	unsigned int imagePixels = height*width;
	unsigned char image[height*width*3];//red,green,blue
	unsigned int imagePointer = 0;

	float smahBoat[2];
	for(int x = 0; x < width; x++){//row
		for(int y = 0; y < height; y++){//column

			//convert location of pixel to "world coordinates"
			smahBoat[0] = (float) ((x*2.0)/height)-1.0 ;
			smahBoat[1] = (float) ((y*2.0)/width)*-1+1.0;
			
			Vec3 pixel(smahBoat[1]*-1,smahBoat[0]*-1,-distanceToCamera);
			Vec3 v = Vec3::subtract(camera->position ,pixel);
			
			//Normalize Vector : Pixel to Camera
			v = Vec3::normalize(v);//ray
			float t = 999;//hopefully t is never higher than this...
			
			Geom* closest = NULL;//calculate closest geom
			Rayhit* hit = new Rayhit();//rayhit for closest geom
			hit->isNull = 1;//initialie the rayhit to null
			Vec3* normal;//required for diffuse and reflection
			
			//attempt to intersect each geometry
				for(int j = 0; j < triangles.size();j++){
					Rayhit* r = triangles.at(j)->intersect(pixel, v, triangles.at(j));
				
				if(r->isNull);
				else if(r->time < t){
					t = r->time;
					Triangle* temp = triangles.at(j);
					closest = temp;
					hit = r;
					isSphere = 0;
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
					isSphere = 1;
					//calculate normal for the sphere
					normal = new Vec3(Vec3::normalize(Vec3::subtract(spheres.at(j)->position, hit->position)));
					}
				}
			if( hit->isNull){//check if no hit

				colorR = 0;
				colorG = 0;
				colorB = 0;
			}
			else{
				if(closest->reflective){//check if hit material is reflective
					Vec3 color;
					if(renderReflections){
					color = (reflection(hit, 0, normal, closest));
					}
				 	else color = Vec3(0,0,0);
				 	
					colorR = color.x*255;
					colorG = color.y*255;
					colorB = color.z*255;
				}
				else{
					//calculate shadow/diffuse
					Vec3 hitToLight = Vec3::normalize(Vec3::subtract(hit->position, light));
					float inShadow = shadow(hit);
					float diffuse = 1;
					diffuse = diffuseIntersections(hit->position, Vec3::normalize(hitToLight), normal);
					
					colorR = closest->color.x*255 * diffuse*inShadow;
					colorG = closest->color.y*255 * diffuse*inShadow;
					colorB = closest->color.z*255 * diffuse*inShadow;
					isSphere = 0;
				}
			}

			image[imagePointer++] = colorR;
			image[imagePointer++] = colorG;
			image[imagePointer++] = colorB;
		}
	} 
	if(mode == 0)
		stbi_write_png("reference.png", width,height,3,image,width*3);
	else if(mode == 1)
		stbi_write_png("custom.png", width,height,3,image,width*3);
	else stbi_write_png("fancy.png", width,height,3,image,width*3);
}


