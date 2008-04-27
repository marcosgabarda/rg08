CXX=g++
CXXFLAGS= -Wall -pedantic
SOURCES=src
LIBS=lib

all: main

main: huffman.o node.o qsort.o 	
	$(CXX) $(SOURCES)/main.cpp $(LIBS)/huffman.o $(LIBS)/node.o $(LIBS)/qsort.o -o $@ $(CXXFLAGS)

node.o:
	$(CXX) $(SOURCES)/node.cpp -c -o $(LIBS)/$@ $(CXXFLAGS)

qsort.o: 
	$(CXX) $(SOURCES)/qsort.cpp -c -o $(LIBS)/$@ $(CXXFLAGS)

huffman.o:
	$(CXX) $(SOURCES)/huffman.cpp -c -o $(LIBS)/$@ $(CXXFLAGS)

debug: clean
	$(CXX) $(SOURCES)/main.cpp $(SOURCES)/huffman.cpp $(SOURCES)/qsort.cpp $(SOURCES)/node.cpp -o $@ $(CXXFLAGS) -g

clean:
	$(RM) -f *~ $(SOURCES)/*~  $(LIBS)/*.o main debug