set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (PROJECT Container) 
 
project (${PROJECT}) 
add_executable (${PROJECT} container.cpp)
add_executable (${PROJECT} main.cpp)