#include "typeword.hpp"
#include "source.hpp"

#include "parseerror.hpp"


bool TypeWord::operator==(const TypeWord& other) const
{
	return (strcmp(data, other.data) == 0);
}

bool TypeWord::operator!=(const TypeWord& other) const
{
	return (strcmp(data, other.data) != 0);
}

bool TypeWord::operator==(const char* str) const
{
	return (strcmp(data, str) == 0);
}

bool TypeWord::operator!=(const char* str) const
{
	return (strcmp(data, str) != 0);
}

TypeWord forceTypeWord(const char* str)
{
	TypeWord word;

	DEBUG_ASSERT(strlen(str) + 1 <= sizeof(TypeWord));

	strcpy(word.data, str);

	return word;
}

TypeWord parseTypeWord(const std::string& str)
{
	TypeWord word;

	DEBUG_ASSERT(str.size() + 1 <= sizeof(TypeWord));
	if (str.size() + 1 > sizeof(TypeWord))
	{
		throw ParseError("Invalid typeword '" + str + "': too long");
	}

	std::copy(str.begin(), str.end(), word.data);

	return word;
}

const char* stringify(const TypeWord& word)
{
	return word.data;
}

std::ostream& operator<<(std::ostream& os, const TypeWord& word)
{
	return os << word.data;
}
