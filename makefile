#Erik Morua 816670615
# makefile for assignment 3 parser
# g++ compiler
CXX=g++
# flags
CXXFLAGS=-std=c++11 -g
# target with output of dbx executable
exp: exp.cpp
	$(CXX) $(CXXFLAGS) -o parser parser.cpp

# call clean to remove executable
clean:
	rm parser