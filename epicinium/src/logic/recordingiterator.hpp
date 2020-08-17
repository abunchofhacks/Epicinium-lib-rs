#pragma once
#include "header.hpp"

#include <fstream>
#include "libs/jsoncpp/json.h"

#include "changeset.hpp"

class TypeNamer;
class Recording;


class RecordingIterator
{
public:
	RecordingIterator(const TypeNamer& typenamer, const Recording& recording);
	~RecordingIterator();
	RecordingIterator(const RecordingIterator&) = delete;
	RecordingIterator(RecordingIterator&&) = delete;
	RecordingIterator& operator=(const RecordingIterator&) = delete;
	RecordingIterator& operator=(RecordingIterator&&) = delete;

private:
	const TypeNamer& _typenamer;
	std::string _name;
	std::ifstream _file;
	size_t _linenumber;

	Json::Reader _reader;
	Json::Value _json;
	std::string _line;

	ChangeSet _changeset;

public:
	const ChangeSet& operator*() const
	{
		return _changeset;
	}

	explicit operator bool() const
	{
		return _file.is_open();
	}

	RecordingIterator& operator++();

	size_t linenumber() const { return _linenumber; }
};
