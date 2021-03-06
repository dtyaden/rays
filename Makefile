default: main.o triangle.o sphere.o camera.o vec3.o 
		g++ main.o triangle.o camera.o vec3.o sphere.o -o ray
		
main.o: main.cpp
		g++ -c main.cpp
		
triangle.o: triangle.cpp
		g++ -c triangle.cpp

camera.o: camera.cpp
		g++ -c camera.cpp
		
vec3.o: vec3.cpp
		g++ -c vec3.cpp
		
sphere.o: sphere.cpp
		g++ -c sphere.cpp

clean:
	rm ray main.o triangle.o camera.o vec3.o sphere.o
run: default
	./ray
