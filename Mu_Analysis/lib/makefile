CXXFLAGS = -fPIC
SOURCES = $(wildcard ../src/*.C)
HEADERS = $(wildcard ../include/*.h)
# not needed, but shows an example of usage for patsubst
OBJS = $(patsubst %.C,%.o,$(SOURCES))

MyDict.cxx: $(HEADERS) Linkdef.h
	rootcling -f $@ -c $(CXXFLAGS) -I../include -p $^

myLib.so: MyDict.cxx $(SOURCES)
	g++ -shared -o$@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include  -I../include $^

clean :
	rm *.so *.d *.pcm *.swp
