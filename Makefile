.PHONY: all clean

all: main.exe

graph.o: graph.cpp graph.h
	g++ -std=c++11 -c graph.cpp -o graph.o

main.o: main.cpp graph.h
	g++ -std=c++11 -c main.cpp -o main.o

main.exe: main.o graph.o
	g++ -std=c++11 main.o graph.o -o main.exe

clean:
	rm -f main.o graph.o main.exe
