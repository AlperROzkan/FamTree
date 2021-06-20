# all the header of the project
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/person.hpp")

# fam_tree library
add_library(fam_tree_lib person.cpp "${HEADER_LIST}")

# make the lib public
target_include_directories(fam_tree_lib PUBLIC "../include")