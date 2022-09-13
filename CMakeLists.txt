cmake_minimum_required(VERSION 3.5)
project(micrograd)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# TODO: go back to c++11?
add_definitions(-O3 -std=c++17 -fPIC -g )
if(APPLE)
	set(CMAKE_CXX_STANDARD 17)
else()
	add_definitions(-lstdc++fs)
	link_libraries(stdc++fs)
endif()


include_directories("${PROJECT_SOURCE_DIR}/micrograd")

add_subdirectory(micrograd)

link_directories(${PROJECT_SOURCE_DIR}/lib)

file(GLOB_RECURSE EXAMPLE_FILES ${PROJECT_SOURCE_DIR}/examples/*.cpp)
foreach(f ${EXAMPLE_FILES})
GET_FILENAME_COMPONENT(fname ${f} NAME_WE )
add_executable(${fname} ${f})
target_link_libraries(${fname} micrograd)
endforeach()