#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP

#include <relation.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace famTree {

	/// <summary>
	/// Converts a relation string to an enum
	/// </summary>
	/// <param name="enumStr">An enum in a string form</param>
	/// <returns>Relation in an enum form</returns>
	Relation convertToRelationEnum(std::string enumStr);

	/// <summary>
	/// Write a string to a file
	/// </summary>
	/// <param name="message">The message to write</param>
	/// <param name="pathToFile">The path to the file</param>
	void writeToFile(std::string message, fs::path pathToFile);

	/// <summary>
	/// Read a string from a file
	/// </summary>
	/// <param name="pathToFile">The path to the file</param>
	/// <returns>The content of the file in a string</returns>
	std::string readFromFile(fs::path path);
}
#endif