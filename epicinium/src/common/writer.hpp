#pragma once
#include "header.hpp"


#if STATIC_WRITER_ENABLED
/* ######################### STATIC_WRITER_ENABLED  ######################### */

class Writer
{
public:
	static std::string write(const Json::Value& json);

private:
	std::unique_ptr<Json::StreamWriter> _writer;

public:
	Writer();

	void install();
};

/* ######################### STATIC_WRITER_ENABLED  ######################### */
#endif
