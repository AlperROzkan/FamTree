cmake_minimum_required(VERSION 3.17...3.20)

# Project description
project(
	FamTree 
	VERSION 0.1.0
	DESCRIPTION "Family genealogy management with cpp"
	LANGUAGES CXX
)

set(CMAKE_CXX_EXTENSIONS OFF)

# Source code here
add_subdirectory(src)

# Executable code here
add_subdirectory(apps)

# Tests here
include(CTest)
include(GoogleTest)
add_subdirectory("${CMAKE_SOURCE_DIR}/extern/googletest")
add_subdirectory(tests)