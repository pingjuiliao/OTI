LLVM_BIN=../../llvm-project/build/bin
CC=$(LLVM_BIN)/clang
CXX=$(LLVM_BIN)/clang++

CFLAGS=-m64 -O0 -fsanitize=oti
CXXFLAGS=$(CFLAGS)


## hello testcases: check c/c++ differences
hellos := hello_c.exe hello_cxx.exe

# tests
tests := employees.exe employees.ll

all: $(hellos) $(tests)
%.ll: %.cc
	$(CXX) $(CXXFLAGS) -S -emit-llvm -o $@ $<
employees.exe: employees.cc
	$(CXX) $(CXXFLAGS) -o $@ $<
hello_c.exe: hello.c
	$(CC) $(CFLAGS) -o $@ $<
hello_cxx.exe: hello.cc
	$(CXX) $(CXXFLAGS) -o $@ $<
clean:
	rm $(wildcard *.exe) $(wildcard *.ll)
