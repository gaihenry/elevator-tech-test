
cmake_minimum_required(VERSION 3.22)

project(test_elevator)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For external libraries
#find_package(LibXml2 REQUIRED)

#Added new source files
set( SOURCES
	elevatorcall.cpp
	elevator.cpp
	dispatcher.cpp
	simulator.cpp
	test_elevator.cpp
)

#Build an executable
add_executable(test ${SOURCES})
