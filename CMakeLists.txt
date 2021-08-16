cmake_minimum_required(VERSION 3.17...3.20)

# Project description
project(
	FamTree 
	VERSION 0.1.0
	DESCRIPTION "Family genealogy management with cpp"
	LANGUAGES CXX
)

# Cmake configuration
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# QT Config and packages
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Includes
set(INCLUDE_DIR
	"/include/"
)

# Variables to use
add_compile_definitions(PROJECT_PATH="${CMAKE_SOURCE_DIR}") # path to this project


# Serialize library
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory("./extern/json")

# Source code here
add_subdirectory("./include/fam_tree/")
#add_subdirectory(src)

# Executable code here
add_subdirectory(apps)

# Tests here
include(CTest)
include(GoogleTest)
add_subdirectory("./extern/googletest")
add_subdirectory(tests)


