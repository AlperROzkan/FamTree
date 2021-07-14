add_executable(
  person_test
  person_test.cpp
)
target_link_libraries(
  person_test
  fam_tree
  gtest_main
)

include_directories("${INCLUDES}")

gtest_discover_tests(person_test)