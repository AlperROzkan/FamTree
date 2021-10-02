########################################
# Cmake configuration
########################################
cmake_minimum_required(VERSION 3.17...3.20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

########################################
### Default Build Type
########################################

# ---
# Cmake has different build types but if none are specified, no optimizations are used.
# ---
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message("######## Setting build type to '${default_build_type}' as none was specified")
    message("######## Setting build type to '${default_build_type}' as none was specified")

    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build" FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

message("######## Build type is '${CMAKE_BUILD_TYPE}', config types are '${CMAKE_CONFIGURATION_TYPES}'")
message("######## Build type is '${CMAKE_BUILD_TYPE}', config types are '${CMAKE_CONFIGURATION_TYPES}'")

########################################
### Project description
########################################

project(
	FamTree 
	VERSION 0.1.0
	DESCRIPTION "Family genealogy management with cpp"
	LANGUAGES CXX
)

########################################
### Setup
########################################

include(CheckIPOSupported)
include(CMakePackageConfigHelpers)
include(InstallRequiredSystemLibraries)
include(FetchContent)
include(GNUInstallDirs)
include(CTest)

find_package(Git)
find_package(Doxygen)

########################################
### Options
########################################
option(PACKAGE_TESTS "Build the tests" ON)

########################################
### Includes
########################################
set(INCLUDE_DIR
	"/include/"
)

########################################
### Dependencies
########################################

# Add the googletest library
add_subdirectory(
    "${PROJECT_SOURCE_DIR}/extern/googletest"
    "extern/googletest"
)

# Serialize library
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory("./extern/json")

# QT
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

########################################
### User made Libraries
########################################
add_library(
	fam_tree 
	"${PROJECT_SOURCE_DIR}/src/person.cpp"
	"${PROJECT_SOURCE_DIR}/src/utils.cpp"
)

########################################
### Targets
########################################

# FamTreeGui : the graphical user interface
set(QTAPP_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/apps")
set(QTAPP_HDR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

qt_add_executable(FamTreeGui
    ${QTAPP_SRC_DIR}/FamTreeGui.cpp
	${QTAPP_HDR_DIR}/view/FamTreeGui.hpp
    ${QTAPP_SRC_DIR}/main.cpp
)

set_target_properties(FamTreeGui 
	PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

# FamTreeCmd : The command line app
add_executable(
	FamTreeCmd
	"${CMAKE_CURRENT_SOURCE_DIR}/apps/FamTreeCmd.cpp"
)

########################################
### Linkage
########################################

# Library fam_tree
# share lib
target_include_directories(
	fam_tree 
	PUBLIC 
	"${PROJECT_SOURCE_DIR}/include/fam_tree"
)

# link fam_tree to other libraries
target_link_libraries(
	fam_tree 
	PUBLIC 
	nlohmann_json::nlohmann_json
)

# compile requirements
target_compile_features(
	fam_tree 
	PUBLIC 
	cxx_std_17
)

# Target FamTreeGui : the GUI app 
# TODO : Why QT and QT6 are mixed ? 
target_link_libraries(FamTreeGui 
	PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

target_link_libraries(FamTreeGui 
	PRIVATE 
	fam_tree
	Qt6::Widgets
	nlohmann_json::nlohmann_json
)

# Target FamTreeCmd : the command line app
target_compile_features(
	FamTreeCmd 
	PRIVATE 
	cxx_std_17
)

target_link_libraries(
	FamTreeCmd 
	PRIVATE 
	fam_tree
	nlohmann_json::nlohmann_json
)

# Variable used in code to find the path to this project
# TODO : Not sure if it works everywhere. Test if its the case.
add_compile_definitions(PROJECT_PATH="${CMAKE_SOURCE_DIR}") # path to this project

########################################
### Tests
########################################
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)

	# SOURCE : https://cliutils.gitlab.io/modern-cmake/chapters/testing/googletest.html
	# keeps the cache cleaner
	mark_as_advanced(
		BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
		gmock_build_tests gtest_build_samples gtest_build_tests
		gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
	)

	# IDE Support
	set_target_properties(gtest PROPERTIES FOLDER extern)
	set_target_properties(gtest_main PROPERTIES FOLDER extern)
	set_target_properties(gmock PROPERTIES FOLDER extern)
	set_target_properties(gmock_main PROPERTIES FOLDER extern)

	# macro to add to 
	macro(package_add_test_with_libraries TESTNAME FILES LIBRARIES)
		add_executable(${TESTNAME} ${FILES})
		target_link_libraries(${TESTNAME} gtest gmock gtest_main ${LIBRARIES})
		gtest_discover_tests(${TESTNAME})
		set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
	endmacro()

	package_add_test_with_libraries(
		person_test 
		"${CMAKE_CURRENT_SOURCE_DIR}/tests/person_test.cpp"
		fam_tree
	)

	package_add_test_with_libraries(
		utils_test 
		"${CMAKE_CURRENT_SOURCE_DIR}/tests/utils_test.cpp"
		fam_tree
	)

endif()




