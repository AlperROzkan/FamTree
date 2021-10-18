cmake_minimum_required(VERSION 3.17...3.20)

project(
        FamTree
        VERSION 0.1.0
        DESCRIPTION "Family genealogy management with cpp"
        LANGUAGES CXX
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

########################################
### Options
########################################
option(PACKAGE_TESTS "Build the tests" ON)

# Variable used in code to find the path to this project
# TODO : Not sure if it works everywhere. Test if its the case.
add_compile_definitions(PROJECT_PATH="${CMAKE_SOURCE_DIR}") # path to this project

########################################
### End Options
########################################

########################################
### Dependencies
########################################

# Add the googletest library
add_subdirectory(
    "${PROJECT_SOURCE_DIR}/extern/googletest"
)

# Serialize library
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory("./extern/json")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

########################################
### End Dependencies
########################################

########################################
### User made Libraries
########################################
add_library(
	fam_tree 
	"${PROJECT_SOURCE_DIR}/src/person.cpp"
	"${PROJECT_SOURCE_DIR}/src/utils.cpp"
)

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
########################################
### End User made Libraries
########################################

########################################
### Qt set up 
########################################

set(PROJECT_SOURCES
        ${PROJECT_SOURCE_DIR}/app/main.cpp
        ${PROJECT_SOURCE_DIR}/app/mainwindow.cpp
        ${PROJECT_SOURCE_DIR}/include/view/mainwindow.h
        ${PROJECT_SOURCE_DIR}/app/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FamTree
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(FamTree SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(FamTree
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(FamTree PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(FamTree PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FamTree)
endif()

########################################
### End Qt set up 
########################################

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
########################################
### End Tests
########################################