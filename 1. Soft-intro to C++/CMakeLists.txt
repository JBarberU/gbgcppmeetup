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

add_executable(example ${SRC} ${HEADERS})

