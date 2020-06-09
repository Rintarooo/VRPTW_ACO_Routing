.PHONY: all clean

all: main.exe

graph.o: graph.cpp graph.h
	g++ -std=c++11 -c graph.cpp -o graph.o

vehicle.o: vehicle.cpp vehicle.h
	g++ -std=c++11 -c vehicle.cpp -o vehicle.o

colony.o: colony.cpp colony.h
	g++ -std=c++11 -c colony.cpp -o colony.o

main.o: main.cpp graph.h vehicle.h colony.h
        g++ -std=c++11 -c main.cpp -o main.o

main.exe: main.o graph.o vehicle.o colony.o
	g++ -std=c++11 main.o graph.o vehicle.o colony.o -o main.exe

clean:
	rm -f *.o main.exe
