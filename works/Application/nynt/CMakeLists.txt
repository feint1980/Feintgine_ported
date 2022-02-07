cmake_minimum_required(VERSION 3.10)

file(GLOB nynt_SRC
	"src/*.h"
	"src/*.cpp"
	)
include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(${CMAKE_SOURCE_DIR}/Feintgine)

include_directories(${CMAKE_SOURCE_DIR}/SDL2)

include_directories(/usr/include/GLES3)


SET(GCC_COVERAGE_COMPILE_FLAGS "-fpermissive -w -pthread")


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")



ADD_EXECUTABLE (nynt ${nynt_SRC})


#target_link_libraries(nynt ${CMAKE_SOURCE_DIR}/lib/libSDL2.a) 
target_link_libraries(nynt /usr/local/lib/libSDL2main.a) 
target_link_libraries(nynt /usr/local/lib/libSDL2.a)
target_link_libraries(nynt ${CMAKE_SOURCE_DIR}/lib/libFeintgine.a)


target_link_libraries(nynt GLESv2)
target_link_libraries(nynt sndio)
#target_link_libraries(nynt GLESv3)

#find_package(SDL2 REQUIRED)
#include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

#set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--start-group,-ldl,-lpthread")
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl -lpthread -lsndio")
