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

all: makedir convertIV

makedir:
	mkdir -p $(OUTLIB);

.PHONY: printmakehelp_and_reminder
printmakehelp_and_reminder:  convertIV.cpp Makefile
	$(info  /******************************************************************************/)
	$(info  * task --> printmakehelp_and_reminder: convertIV.cpp Makefile                 *)
	$(info  * $$@ ----> $@                                         *)
	$(info  * $$< --------------------------------> $<                          *)
	$(info  * $$^ --------------------------------> $^                 *)
	$(info  /******************************************************************************/)

obj/convertIV.o: convertIV.cpp infoStr.hh
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

obj/libconvertIV.so: obj/convertIV.o
	$(CXX) -shared -o $@ $^

convertIV: convertIV.cpp infoStr.hh
	$(CXX) -o $@ $^ $(CXXFLAGS)

install: makedir obj/libwfsim.so
	mkdir -p $(INSTALLDIR);
	cp $(OUTLIB)libwfsim.so $(INSTALLDIR)libwfsim.so
	cp src/*.hh $(INSTALLDIR).

cleaninstall:
	rm -rf $(INSTALLDIR)

clean:
	rm -f convertIV
	rm -f *~
	rm -f .*~
	rm -f $(OUTLIB)*.o
	rm -f $(OUTLIB)*.so
