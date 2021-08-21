# SOURCE : https://cliutils.gitlab.io/modern-cmake/chapters/testing/googletest.html

# add the googletest library
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")

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
    person_test.cpp 
    fam_tree
)

package_add_test_with_libraries(
    utils_test 
    utils_test.cpp 
    fam_tree
)
