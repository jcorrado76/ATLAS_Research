CXXFLAGS = -fPIC
SOURCES = ComputeL1XE30toZBEfficiency.C ../BurrTemplateSelector/Jburr_Template_Selector.C
HEADERS = ComputeL1XE30toZBEfficiency.h ../BurrTemplateSelector/Jburr_Template_Selector.h

MyDict.cxx: $(HEADERS) Linkdef.h
	rootcling -f $@ -c $(CXXFLAGS) -I../BurrTemplateSelector/ -p $^

myLib.so: MyDict.cxx $(SOURCES)
	g++ -shared -o$@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include  -I../BurrTemplateSelector $^
	echo "Made the library"

clean :
	rm *.so *.d *.pcm *.swp
