#pragma once

#include "print_functions.h"

#include <utility>
#include <vector>
#include <set>
#include <map>

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& out, const std::pair<Key, Value>& container)
{
	out << container.first;
	out << ": ";
	out << container.second;
	return (out);
}

template <typename Term>
std::ostream& operator<<(std::ostream& out, const std::vector<Term>& container)
{
	out << '[';
	Print(out, container);
	out << ']';
	return (out);
}

template <typename Term>
std::ostream& operator<<(std::ostream& out, const std::set<Term>& container)
{
	out << '{';
	Print(out, container);
	out << '}';
	return (out);
}

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& out, const std::map<Key, Value>& container)
{
	out << '{';
	Print(out, container);
	out << '}';
	return (out);
}
