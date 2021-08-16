add_executable(
  person_test
  person_test.cpp
)

add_executable(
	utils_test
	utils_test.cpp
)

target_include_directories(
	person_test 
	PRIVATE
	"${INCLUDE_DIR}"
)

target_link_libraries(
  person_test
  fam_tree
  gtest_main
  nlohmann_json::nlohmann_json
)

target_include_directories(
	utils_test 
	PRIVATE
	"${INCLUDE_DIR}"
)

target_link_libraries(
  utils_test
  fam_tree
  gtest_main
  nlohmann_json::nlohmann_json
 )

gtest_discover_tests(person_test)
gtest_discover_tests(utils_test)