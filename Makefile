# How to build the project
build:
	g++ -std=c++17 main.cpp mentor.cpp -o mentor_system

# How to run it
run:
	./mentor_system

# This cleans up the messy .o files or the executable
clean:
	rm -f mentor_system