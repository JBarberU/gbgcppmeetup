cmake_minimum_required(VERSION 2.8)

project(cppmeetup)

set(SRC
  src/example.cpp
)

set(HEADERS
  src/example.hpp
)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
endif()

add_library(foo src/Foo.cpp)

add_executable(example ${SRC} ${HEADERS})
if(NOT WIN32)
  set(ADDITIONAL_LIBS pthread)
endif()
target_link_libraries(example foo ${ADDITIONAL_LIBS})

