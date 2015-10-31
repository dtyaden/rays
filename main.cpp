#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

int height, width;

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
	height = 512;
	width = 512;
	unsigned int imagePixels = height*width;
	unsigned char image[height*width*3];//red,green,blue
	makeImage(image, imagePixels);
	for (int i = 0; i < imagePixels*3; i++){
		cout<< image[i]<<"\n";
	}
	
	cout << stbi_write_png("dummy.png", width,height,3,image,width*3) << "\n";
	cout << "dumb\n";
}
