CXXFLAGS = -fPIC
SOURCES = $(wildcard ../src/*.C)
HEADERS = $(wildcard ../include/*.h)
# not needed, but shows an example of usage for patsubst
OBJS = $(patsubst %.C,%.o,$(SOURCES))

myLib.so: MyDict.cxx $(SOURCES)
	g++ -shared -o$@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include  -I../include $^

MyDict.cxx: $(HEADERS) Linkdef.h
	rootcling -f $@ -c -I../include -p $^

# to prevent the error messages when certain filetypes are not present, pipe output to dev/null
# the @ is also used to suppress output, but it just won't suppress errors
clean :
	@rm *.so *.d *.pcm *.swp 2>/dev/null || true
