#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP

#include <relation.hpp>
#include <string>

namespace famTree {

	/// <summary>
	/// Converts a relation string to an enum
	/// </summary>
	/// <param name="enumStr">An enum in a string form</param>
	/// <returns>Relation in an enum form</returns>
	Relation convertToRelationEnum(std::string enumStr);

}
#endif