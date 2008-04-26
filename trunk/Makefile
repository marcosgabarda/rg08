CXX=g++
CXXFLAGS= -Wall -pedantic
SOURCES=src
LIBS=lib

all: main

main:
	$(CXX) $(SOURCES)/main.cpp $(SOURCES)/qsort.cpp $(SOURCES)/huffman.cpp $(SOURCES)/node.cpp -o $@ $(CXXFLAGS)

clean:
	$(RM) -f *~ $(SOURCES)/*~  $(LIBS)/*.o main