LLVM_BIN=../../llvm-project/build/bin
CC=$(LLVM_BIN)/clang
CXX=$(LLVM_BIN)/clang++

CFLAGS=-m64 -O0
CXXFLAGS=$(CFLAGS)
OTIFLAGS=-fsanitize=oti

# tests
tests := employees_oti.exe employees.ll employees_vuln.exe
tests += account_oti.exe account_vuln.exe
tests += tomato_oti.exe
.PHONY: clean

all: $(hellos) $(tests)
%.ll: %.cc
	$(CXX) $(CXXFLAGS) -S -emit-llvm -o $@ $<
%_vuln.exe: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<
%_oti.exe: %.cc
	$(CXX) $(CXXFLAGS) $(OTIFLAGS) -o $@ $<
clean:
	rm $(wildcard *.exe) $(wildcard *.ll)
