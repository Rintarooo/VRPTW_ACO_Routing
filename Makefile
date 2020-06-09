.PHONY: all clean
program = main.exe
objs = graph.o vehicle.o colony.o main.o
CXX = g++ -std=c++11
RM = rm -f
CFLAGS = -Wall -g 
# -g is for debuger; lldb for MacOS

all: main.exe
clean:
	$(RM) $(objs) $(program)

$(program): $(objs) 
	$(CXX) $(CFLAGS) $(objs) -o $@

.SUFFIXES: .c .o
.c.o:
	$(CXX) $(CFLAGS) -c $<