CXX=clang++
CXXFLAGS=-m64 -fPIC -I../../include

LOAD_LIB=-L. -lOTI
all: test_lib.exe
libOTI.so: ../../lib/liboti.cc
	$(CXX) $(CXXFLAGS) -shared -o $@ $<
test_lib.exe: ./test_lib.cc libOTI.so
	$(CXX) $(CXXFLAGS) $(LOAD_LIB) -o $@ $<
clean:
	rm $(wildcard *.exe) $(wildcard *.so)

