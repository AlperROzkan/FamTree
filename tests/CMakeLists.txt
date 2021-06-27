add_executable(
  person_test
  person_test.cpp
)
target_link_libraries(
  person_test
  fam_tree
  gtest_main
)

gtest_discover_tests(person_test)