add_executable(
	FamTreeCmd
	"FamTreeCmd.cpp"
)

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