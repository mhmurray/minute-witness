all: testcpp libDataClasses.so libDataClasses.rootmap

ROOT_CFLAGS = `$(ROOTSYS)/bin/root-config --cflags`
ROOT_LIBS = `$(ROOTSYS)/bin/root-config --libs` -lTree

CXX = g++
CXXFLAGS = -g -ansi -pedantic -Wall $(ROOT_CFLAGS) -fPIC -I$(ROOTSYS)/include
OBJECTS = Event.o
HEADERS = Event.h

CURRENT_DIR=$(shell pwd)

testcpp: main.cpp $(CURRENT_DIR)/libDataClasses.so
	$(CXX) $(CXXFLAGS) -o $@ $^ -Wl,--no-as-needed $(ROOT_LIBS) -L$(MU) -lMucapEvent

DataClassesDict.cpp: $(HEADERS) LinkDef.h
	$(ROOTSYS)/bin/rootcint -f $@ -c $^

$(CURRENT_DIR)/libDataClasses.so: $(OBJECTS) DataClassesDict.o
	$(CXX) -Wl,--no-as-needed $(ROOT_LIBS)  -shared -fPIC -o $@ $(shell root-config --ldflags) -I$(ROOTSYS)/include $^

libDataClasses.rootmap: libDataClasses.so LinkDef.h
	rlibmap -f -o $@ -l libDataClasses.so -c LinkDef.h

.PHONY: clean cleantree testtree
event_tree.root: libDataClasses.rootmap makeTree.cpp
	root -l -b -q makeTree.cpp+

testtree: event_tree.root
	root -l -b -q testTree.cpp

clean:
	rm -f *.o testcpp DataClassesDict.* *.so *.d libDataClasses.rootmap

cleantree:
	rm -f event_tree.root
