#include "utils.hpp"

Relation famTree::convertToRelationEnum(std::string enumStr)
{
	if (enumStr == "child") return Relation::child;
	else if (enumStr == "parent") return Relation::parent;
	else if (enumStr == "spouse") return Relation::spouse;
	else if (enumStr == "sibling") return Relation::sibling;

	return Relation::error;
}