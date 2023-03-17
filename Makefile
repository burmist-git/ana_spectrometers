RELVERSION  = $(shell cat .release)

ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

MakefileFullPath = $(abspath $(lastword $(MAKEFILE_LIST)))
MakefileDirFullPath = $(shell dirname $(MakefileFullPath))
INSTALLDIR = $(MakefileDirFullPath)/install.$(RELVERSION)/

CXX  = g++
CXX += -I./

CXXFLAGS  = -g -Wall -fPIC -Wno-deprecated
CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += $(ROOTLIBS)
CXXFLAGS += $(ROOTGLIBS)
CXXFLAGS += -std=c++14
CXXFLAGS += -fconcepts

OUTLIB = ./obj/

#----------------------------------------------------#

all: makedir convert_spec_avantes

makedir:
	mkdir -p $(OUTLIB);

.PHONY: printmakehelp_and_reminder
printmakehelp_and_reminder: convert_spec_avantes.cpp Makefile
	$(info  /******************************************************************************/)
	$(info  * task --> printmakehelp_and_reminder: convert_spec_avantes.cpp Makefile                 *)
	$(info  * $$@ ----> $@                                         *)
	$(info  * $$< --------------------------------> $<                          *)
	$(info  * $$^ --------------------------------> $^                 *)
	$(info  /******************************************************************************/)

obj/convert_spec_avantes.o: convert_spec_avantes.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

obj/libconvert_spec_avantes.so: obj/convert_spec_avantes.o
	$(CXX) -shared -o $@ $^

convert_spec_avantes: convert_spec_avantes.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS)

install: makedir obj/libconvert_spec_avantes.so
	mkdir -p $(INSTALLDIR);
	cp $(OUTLIB)libconvert_spec_avantes.so $(INSTALLDIR)libconvert_spec_avantes.so
	cp src/*.hh $(INSTALLDIR).

cleaninstall:
	rm -rf $(INSTALLDIR)

clean:
	rm -f convert_spec_avantes
	rm -f *~
	rm -f .*~
	rm -f $(OUTLIB)*.o
	rm -f $(OUTLIB)*.so
