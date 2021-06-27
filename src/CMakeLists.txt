set(HEADER_LIST 
	"${CMAKE_SOURCE_DIR}/include/gender.hpp"
	"${CMAKE_SOURCE_DIR}/include/relation.hpp"
	"${CMAKE_SOURCE_DIR}/include/person.hpp"
)

# make library
add_library(
	fam_tree 
	person.cpp 
	${HEADER_LIST}
)

# share lib
target_include_directories(
	fam_tree 
	PUBLIC 
	"${CMAKE_SOURCE_DIR}/include"
)

# compile requirements
target_compile_features(
	fam_tree 
	PUBLIC 
	cxx_std_17
)