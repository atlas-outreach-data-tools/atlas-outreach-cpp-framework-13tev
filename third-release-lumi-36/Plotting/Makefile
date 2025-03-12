### Makefile in case you want to use 'make'
LIBS = `root-config --glibs` -L/usr/X11R6/lib -lm -ldl -lstdc++  
TOOL = -I../tools
CXXFLAGS = --exceptions -I$(ROOTSYS)/include

OBJECTS = Plotting.o 

optflags = -O3 -march=core2 -msse -msse2 -msse3 -mfpmath=sse -Wno-deprecated -Wwrite-strings

debugflags = -g -pg -ggdb -Wall
 
all: $(OBJECTS)
	gcc $(optflags) $(debugflags) $(OPTCOMP) $(CXXFLAGS) $(LIBS) -o plot -g $(OBJECTS) 	

Plotting.o: Plotting.cxx Plotting.h
	gcc $(optflags) $(debugflags) $(OPTCOMP) ${CXXFLAGS} -c Plotting.cxx

clean:
	rm -f Plotting.o
	rm -f plot
	rm -rf gmon.out
	rm -f *~;
