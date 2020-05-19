cmake_minimum_required(VERSION 3.16)
project(trashbox)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -ggdb")

set(HEADERS
		exceptions.h)

set(SOURCES
		main.cpp
		exceptions.cpp)


add_executable(trashbox ${SOURCES} ${HEADERS})
