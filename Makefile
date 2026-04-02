# Variables make it easier to change compiler or flags later
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# The default target (what runs when you just type 'make')
all: build

# build depends on the source and header files
build: main.cpp mentor.cpp mentor.h
	$(CXX) $(CXXFLAGS) main.cpp mentor.cpp -o mentor_system

run:
	./mentor_system

clean:
	rm -f mentor_system