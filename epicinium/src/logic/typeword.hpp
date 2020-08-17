#pragma once
#include "header.hpp"


struct TypeWord
{
	char data[16] = {};

	bool operator==(const TypeWord& other) const;
	bool operator!=(const TypeWord& other) const;
	bool operator==(const char* other) const;
	bool operator!=(const char* other) const;
};

TypeWord forceTypeWord(const char* str);

TypeWord parseTypeWord(const std::string& str);
const char* stringify(const TypeWord& word);

std::ostream& operator<<(std::ostream& os, const TypeWord& word);
