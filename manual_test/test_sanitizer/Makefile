LLVM_BIN=../../llvm-project/build/bin
CC=$(LLVM_BIN)/clang
CXX=$(LLVM_BIN)/clang++

CFLAGS=-m64 -O0
CXXFLAGS=$(CFLAGS)
OTIFLAGS=-fsanitize=oti

## hello testcases: check c/c++ differences
hellos := hello_c.exe hello_cxx.exe

# tests
tests := employees_oti.exe employees.ll employees_vuln.exe
tests += account_oti.exe account_vuln.exe
.PHONY: clean

all: $(hellos) $(tests)
%.ll: %.cc
	$(CXX) $(CXXFLAGS) -S -emit-llvm -o $@ $<
%_vuln.exe: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<
%_oti.exe: %.cc
	$(CXX) $(CXXFLAGS) $(OTIFLAGS) -o $@ $<
hello_c.exe: hello.c
	$(CC) $(CFLAGS) -o $@ $<
hello_cxx.exe: hello.cc
	$(CXX) $(CXXFLAGS) -o $@ $<
clean:
	rm $(wildcard *.exe) $(wildcard *.ll)
