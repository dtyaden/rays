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



int main(int argc, char *argv[]){
	height = 8;
	width = 8;
	float distanceToCamera = 2;

	camera = new Camera(Vec3(0,0,0), distanceToCamera, (float) width, (float) width);
	Vec3 x(0,0,0);
	Vec3 y(0,1,0);
	Vec3 z(1,0,0);
	scene.push_back(new Triangle(x,y,z, Vec3(255,0,0)));
	scene.push_back(new Sphere(4,Vec3(0,0,-3), Vec3(255,0,0)));
	unsigned int imagePixels = height*width;
	unsigned char image[height*width*3];//red,green,blue
	//makeImage(image, imagePixels);

	float smahBoat[2];
	for(int x = 0; x < width; x++){//row
		for(int y = 0; y < height; y++){//column
			smahBoat[0] = (float) ((x*2.0)/height)-1.0 ;
			smahBoat[1] = (float) ((y*2.0)/width)*-1+1.0;
			Vec3 v = Vec3::subtract(camera->position ,Vec3(smahBoat[0],smahBoat[1],-distanceToCamera));
			//cout<< v.x<< " " << v.y<< " " <<v.z<< "\n";
			cout<< smahBoat[0] << " " << smahBoat[1] << "\n";
			v = Vec3::normalize(v);//ray
			Ray r(v, camera->position);
			//cout << v.x<<" "<<v.y << " " << v.z <<"\n";
		}
	} 
	
	cout << stbi_write_png("dummy.png", width,height,3,image,width*3) << "\n";
	cout << "dumb\n";
}
