cmake_minimum_required(VERSION 3.17.0)

# Project description
project (FamTree 
	VERSION 0.1.0
	DESCRIPTION "Family genealogy management with cpp"
	LANGUAGES CXX
)

# Add test support
include(CTest)
enable_testing()

# add_executable(FamTree main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Source code here
add_subdirectory(src)

# Executable code here
add_subdirectory(apps)

# Tests here
# add_subdirectory(tests)

