#SET(CMAKE_C_COMPILER ${PROJECT_SOURCE_DIR}/llvm-project/build/bin/clang)
#SET(CMAKE_CXX_COMPILER ${PROJECT_SOURCE_DIR}/llvm-project/build/bin/clang++)
SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)

SET(CMAKE_C_FLAGS "-Wall -shared -m64 -fPIC -O3")


add_library(OTI OBJECT
  liboti.cc
  "${PROJECT_SOURCE_DIR}/include/liboti.h")

target_include_directories(OTI PUBLIC
  ${PROJECT_SOURCE_DIR}/include)
