cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (PROJECT Container) 
 
project (${PROJECT}) 
set (SOURCES 
	     main.cpp)

add_executable (${PROJECT} ${SOURCES})
