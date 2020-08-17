#pragma once
#include "header.hpp"


class ParseError : public std::runtime_error
{
public:
	explicit ParseError(const std::string& what_arg) :
		std::runtime_error(what_arg)
	{}

	explicit ParseError(const char* what_arg) :
		std::runtime_error(what_arg)
	{}
};
