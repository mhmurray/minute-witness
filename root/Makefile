all: testcpp libDataClasses.so libDataClasses.rootmap

ROOT_CFLAGS = `$(ROOTSYS)/bin/root-config --cflags`
ROOT_LIBS = `$(ROOTSYS)/bin/root-config --libs`

CXX = g++
CXXFLAGS = -g -Wall $(ROOT_CFLAGS) -fPIC -I$(ROOTSYS)/include
OBJECTS = Event.o
HEADERS = Event.h

CURRENT_DIR=$(shell pwd)

testcpp: main.cpp $(CURRENT_DIR)/libDataClasses.so
	$(CXX) $(CXXFLAGS) -o $@ $^ $(ROOT_LIBS)

DataClassesDict.cpp: $(HEADERS) LinkDef.h
	$(ROOTSYS)/bin/rootcint -f $@ -c $^

$(CURRENT_DIR)/libDataClasses.so: $(OBJECTS) DataClassesDict.o
	$(CXX) $(ROOT_LIBS)  -shared -fPIC -o $@ $(shell root-config --ldflags) -I$(ROOTSYS)/include $^

libDataClasses.rootmap: libDataClasses.so LinkDef.h
	rlibmap -f -o $@ -l libDataClasses.so -c LinkDef.h

.PHONY: clean
clean:
	rm -f *.o testcpp DataClassesDict.* libDataClasses.so libDataClasses.rootmap
