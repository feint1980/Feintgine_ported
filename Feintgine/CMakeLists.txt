cmake_minimum_required(VERSION 3.10)


file(GLOB Feintgine_SRC
	"src/*.h"
	"src/*.cpp"
	"src/*.cc"
	)
include_directories(${CMAKE_SOURCE_DIR}/include)
#include_directories(/usr/include/GLES3)
include_directories(/usr/include/GLES2)
SET(GCC_COVERAGE_COMPILE_FLAGS "-fpermissive -w")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

ADD_LIBRARY(Feintgine STATIC
	${Feintgine_SRC})

