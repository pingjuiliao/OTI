#include "oti.h"

#include <asm/prctl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

// #ifndef DEBUG
// #define DEBUG
// #endif

#ifndef OTI_VERBOSE
#define OTI_VERBOSE
#endif

int __attribute((constructor)) oti_init() {
  int r;
  void* metadata_base = mmap(NULL, FIRST_LVL_SIZE, 
                        PROT_READ|PROT_WRITE, 
                        MAP_ANONYMOUS|MAP_PRIVATE,
                        -1, 0);
  if (!metadata_base) {
    fprintf(stderr, "[Error] unable to map metadata");
    exit(-1);
  }
  memset(metadata_base, 0, FIRST_LVL_SIZE);
  r = syscall(SYS_arch_prctl, ARCH_SET_GS, metadata_base);
  if (r != 0) {
    fprintf(stderr, "[Error] unable to gs error");
    exit(-1);
  }
  metadata_base = NULL;
#ifdef DEBUG
  puts("[OTI] Metadata region Success");
#endif
  return 0;
}

void oti_vptr_store(void** vptr) {
  void* top_entry = NULL;
  size_t top_idx = 0;
  size_t bot_idx = 0;

#ifdef OTI_VERBOSE
  printf("[OTI_STORE] map[%p] := %p\n", vptr, *vptr);
#endif

#ifdef DEBUG
  printf("oti_vptr_store: vptr == %p\n", vptr);
  printf("oti_vptr_store: *vptr == %p\n", *vptr);
#endif
  asm volatile(
      "movq %[vptr], %[top_idx];"
      "shrq $23, %[top_idx];"
      "andq $0x1fffff8, %[top_idx];"
      "movq %[vptr], %[bot_idx];"
      "andq $0x3fffff8, %[bot_idx]"
      : [top_idx]"=m"(top_idx),
        [bot_idx]"=m"(bot_idx)
      : [vptr]"r"(vptr)
  );

#ifdef DEBUG
  printf("oti_vptr_store: top_idx == %p\n", (void *)top_idx);
  printf("oti_vptr_store: bot_idx == %p\n", (void *)bot_idx);
#endif

  asm volatile(
      "movq %%gs:(%[top_idx]), %[top_entry];"
      : [top_entry] "=r"(top_entry)
      : [top_idx] "r"(top_idx)
  );
  
  if (top_entry == NULL) {
    top_entry = mmap(NULL, SECOND_LVL_SIZE,
                     PROT_READ|PROT_WRITE,
                     MAP_ANONYMOUS|MAP_PRIVATE,
                     -1, 0);
#ifdef DEBUG
    printf("oti_vptr_store: top_entry == %p\n", top_entry);
    // printf("oti_vptr_store: top_entry size == %p\n", SENCODE_LVL_SIZE);
    printf("oti_vptr_store: top_entry_end == %p\n", 
            (void *)(((size_t) top_entry) + (SECOND_LVL_SIZE)));
#endif
    asm volatile(
        "movq %[top_entry], %%gs:(%[top_idx]);"
        : 
        : [top_entry] "r"(top_entry),
          [top_idx] "r"(top_idx)
    );
  }
  
  asm volatile(
    "movq (%[vptr]), %%r10;"
    "movq %%r10, (%[top_entry], %[bot_idx]);"
    :
    : [vptr] "r"(vptr),
      [top_entry] "r"(top_entry),
      [bot_idx] "r"(bot_idx)
  );
  
  top_entry = NULL;
}

void oti_vptr_check(void** vptr) {
  void* top_entry = NULL;
  size_t top_idx, bot_idx;
  void* secured_copy;
  asm volatile(
    "movq %[vptr], %[top_idx];"
    "shrq $23, %[top_idx];"
    "andq $0x1fffff8, %[top_idx];"
    "movq %[vptr], %[bot_idx];"
    "andq $0x3fffff8, %[bot_idx];"
    : [top_idx] "=m"(top_idx),
      [bot_idx] "=m"(bot_idx) 
    : [vptr] "r"(vptr)
  );
#ifdef OTI_VERBOSE
  printf("[OTI_CHECK] map[%p] == %p?\n", vptr, *vptr);
#endif

#ifdef DEBUG
  printf("oti_vptr_check: vptr == %p\n", vptr);
  printf("oti_vptr_check: *vptr == %p\n", *vptr);
  printf("oti_vptr_check: top_idx == %p\n", (void *)top_idx);
  printf("oti_vptr_check: bot_idx == %p\n", (void *)bot_idx);
#endif
  asm volatile(
    "movq %%gs:(%[top_idx]), %[top_entry];"
    : [top_entry] "=r"(top_entry)
    : [top_idx] "r"(top_idx)
  );
  if (!top_entry) {
    fprintf(stderr, 
            OTI_ERROR_BANNER
            "The field has not been protected\n");
    exit(-1);
  }

#ifdef DEBUG
  printf("oti_vptr_check: top_entry == %p\n", top_entry);
  printf("oti_vptr_check: access == %p\n",
          (void *)(((size_t) top_entry) + ((size_t) bot_idx)));
#endif
  
  asm volatile(
    "movq (%[top_entry], %[bot_idx]), %[secured_copy];"
    : [secured_copy] "=r"(secured_copy)
    : [top_entry] "r"(top_entry),
      [bot_idx] "r"(bot_idx)
  );  

  if (secured_copy != *vptr) {
    fprintf(stderr,
            OTI_ERROR_BANNER 
            "virtual pointer has been changed\n");
    fprintf(stderr, "  Before: %p\n", secured_copy);
    fprintf(stderr, "  After : %p\n", *vptr);
    exit(-1);
  }
}


void oti_hello(void) {
  puts("[OTI] hello ctor");
}
