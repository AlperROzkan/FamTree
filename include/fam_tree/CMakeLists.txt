# make library
add_library(
	fam_tree 
	"../../src/person.cpp"
	"../../src/utils.cpp"
)

# share lib
target_include_directories(
	fam_tree 
	PUBLIC 
	"./"
)

target_link_libraries(
	fam_tree 
	PRIVATE 
	nlohmann_json::nlohmann_json
)

# compile requirements
target_compile_features(
	fam_tree 
	PUBLIC 
	cxx_std_17
)