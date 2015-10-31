default: main.o
		g++ main.o -o ray
		
main.o: main.cpp
		g++ -c main.cpp

clean:
	rm ray main.o
