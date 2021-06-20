# include path
set(INCLUDES "${PROJECT_SOURCE_DIR}/include")

# all the header of the project
set(HEADER_LIST 
	"${INCLUDES}/person.hpp"
	"${INCLUDES}/gender.hpp"
	"${INCLUDES}/relation.hpp"
)

# fam_tree library
add_library(fam_tree_lib person.cpp "${HEADER_LIST}")

# make the lib public
target_include_directories(fam_tree_lib PUBLIC "../include")