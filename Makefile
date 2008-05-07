CXX=g++
CXXFLAGS= -Wall -pedantic
SOURCES=src
LIBS=lib
LDLIBS=-lm

all: huf unhuf

huf: huffman.o node.o qsort.o utils.o
	$(CXX) $(SOURCES)/huf.cpp $(LIBS)/huffman.o $(LIBS)/node.o $(LIBS)/qsort.o $(LIBS)/utils.o -o $@ $(CXXFLAGS) $(LDLIBS)

unhuf: huffman.o node.o qsort.o utils.o
	$(CXX) $(SOURCES)/unhuf.cpp $(LIBS)/huffman.o $(LIBS)/node.o $(LIBS)/qsort.o $(LIBS)/utils.o -o $@ $(CXXFLAGS) $(LDLIBS)

node.o:
	$(CXX) $(SOURCES)/node.cpp -c -o $(LIBS)/$@ $(CXXFLAGS)

qsort.o: 
	$(CXX) $(SOURCES)/qsort.cpp -c -o $(LIBS)/$@ $(CXXFLAGS)

huffman.o:
	$(CXX) $(SOURCES)/huffman.cpp -c -o $(LIBS)/$@ $(CXXFLAGS)

utils.o:
	$(CXX) $(SOURCES)/utils.cpp -c -o $(LIBS)/$@ $(CXXFLAGS)

debug: clean
	$(CXX) $(SOURCES)/main.cpp $(SOURCES)/huffman.cpp $(SOURCES)/qsort.cpp $(SOURCES)/node.cpp -o $@ $(CXXFLAGS) -g

clean:
	$(RM) -f *~ $(SOURCES)/*~  $(LIBS)/*.o main debug