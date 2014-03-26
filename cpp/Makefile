all: testcpp

CXX = g++
CXXFLAGS = -g -Wall -fPIC

CURRENT_DIR=$(shell pwd)

testcpp: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ -Wl,--no-as-needed

.PHONY: clean cleantree testtree
clean:
	rm -f *.o testcpp
