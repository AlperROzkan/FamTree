add_executable (FamTree "FamTree.cpp")
target_compile_features(FamTree PRIVATE cxx_std_17)

target_link_libraries(FamTree PRIVATE fam_tree_lib)