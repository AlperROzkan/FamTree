include_directories("${INCLUDES}")

# make library
add_library(
	fam_tree 
	person.cpp 
)

# share lib
target_include_directories(
	fam_tree 
	PUBLIC "${CMAKE_SOURCE_DIR}/include"
)

# compile requirements
target_compile_features(
	fam_tree 
	PUBLIC 
	cxx_std_17
)