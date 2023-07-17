#include <iostream>
#include <cstring>

#include <stdio.h>

#include "oti.h"

struct Overflowable {
  char buf[0x10];
  int (*fptr)(const char*);
};


int main(int argc, char** argv) {
  Overflowable ovfl;
  ovfl.fptr = puts; 
  oti_vptr_store((void **) &ovfl.fptr);
  strcpy(ovfl.buf, "Hello, my name is pingjui. you are about to be overflowed");
    
  oti_vptr_check((void **) &ovfl.fptr);
  (*ovfl.fptr)((const char *)ovfl.buf);
  return 0;
}
