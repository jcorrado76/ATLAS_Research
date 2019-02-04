CXXFLAGS = -Wall -fPIC
SOURCES = $(wildcard ../src/*.C)
HEADERS = $(wildcard ../include/*.h)
# not needed, but shows an example of usage for patsubst
OBJS = $(patsubst %.C,%.o,$(SOURCES))

INCLUDE_FLAG = -I$(ROOTSYS)/include -I../include

myLib.so: MyDict.cxx $(SOURCES)
	g++ -shared -o$@ `root-config --ldflags` $(CXXFLAGS) $(INCLUDE_FLAG) $^

MyDict.cxx: $(HEADERS) Linkdef.h
	rootcling -v -f $@ -c $(CXXFLAGS) $(INCLUDE_FLAG) $^

# to prevent the error messages when certain filetypes are not present, pipe output to dev/null
# the @ is also used to suppress output, but it just won't suppress errors
clean :
	@rm MyDict* *.so *.d *.pcm *.swp 2>/dev/null || true
