#ifndef RELATION_HPP
#define RELATION_HPP

#pragma once
enum class Relation
{
	grandParent,
	parent,
	stepParent,
	child,
	stepChild,
	sibling,
	spouse,
	stepSibling,
	halfSibling,
	cousin,
	error,
	other
};

#endif // !RELATION_HPP 