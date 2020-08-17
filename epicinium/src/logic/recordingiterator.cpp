#include "recordingiterator.hpp"
#include "source.hpp"

#include "recording.hpp"


RecordingIterator::RecordingIterator(
		const TypeNamer& typenamer, const Recording& recording) :
	_typenamer(typenamer),
	_name(recording.name()),
	_file(recording.filename()),
	_linenumber(0)
{
	if (!_file) return;

	if (!std::getline(_file, _line) || !_reader.parse(_line, _json)
		|| (!_json.isObject() && !_json.isArray()))
	{
		_file.close();
		return;
	}

	// Pre-historic recording?
	if (!_json.isObject())
	{
		_changeset = ChangeSet(_typenamer, _json);
	}
	else
	{
		++(*this);
	}
}

RecordingIterator::~RecordingIterator() = default;

RecordingIterator& RecordingIterator::operator++()
{
	if (!_file) return *this;

	if (!std::getline(_file, _line) || !_reader.parse(_line, _json)
		|| !_json.isArray())
	{
		_file.close();
		return *this;
	}

	_changeset = ChangeSet(_typenamer, _json);
	++_linenumber;

	return *this;
}
