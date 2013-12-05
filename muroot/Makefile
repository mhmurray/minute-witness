all: testcpp libDataClasses.so libDataClasses.rootmap

ROOT_CFLAGS = `$(ROOTSYS)/bin/root-config --cflags`
ROOT_LIBS = `$(ROOTSYS)/bin/root-config --libs` -lTree


CURRENT_DIR=$(shell pwd)

UIUC_INCLUDE_DIRS = $(MU)/../src/uiuc:$(MU)/../src/uiuc/Display:$(MU)/../src/uiuc/Parameters:$(MU)/../src/uiuc/Raw:$(MU)/../src/uiuc/Muon:$(MU)/../src/uiuc/Electron:$(MU)/../src/uiuc/Example:$(MU)/../src/uiuc/Clustering:$(MU)/../src/uiuc/MuonElectron/:$(MU)/../src/uiuc/Lifetime:$(MU)/../src/uiuc/Calibration:$(MU)/../src/uiuc/DisplayTrigger:$(MU)/../src/uiuc/Spark:$(MU)/../src/uiuc/Francoise:$(MU)/../src/uiuc/Efficiencies:$(MU)/../src/uiuc/SpecialAutocorr:$(MU)/../src/uiuc/Background:$(MU)/../src/uiuc/HotWires:$(MU)/../src/uiuc/EventTree:$(MU)/../src/uiuc/Fadc:$(MU)/../src/uiuc/SrimStudy:$(MU)/../src/uky:$(MU)/../src/uiuc/macros/EventTree/src/:$(MU)/../src/shared:$(MU)/../src/uiuc/TPC:$(MU)/../src/uiuc/Online:$(MU)/../src/uiuc/Neutron:$(MU)/../src/uiuc/MCTruth
UIUC_CFLAGS = $(patsubst %,-I%,$(subst :, ,$(UIUC_INCLUDE_DIRS)))

CXX = g++
CXXFLAGS = -g -Wall $(ROOT_CFLAGS) -fPIC -I$(ROOTSYS)/include $(UIUC_CFLAGS)
OBJECTS = Event.o
HEADERS = Event.h

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
	rm -f *.o testcpp DataClassesDict.* libDataClasses.rootmap *.so *.d

cleantree:
	rm -f event_tree.root
