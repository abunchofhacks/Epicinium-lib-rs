#include "source.hpp"
#include "writer.hpp"


#if STATIC_WRITER_ENABLED
/* ######################### STATIC_WRITER_ENABLED  ######################### */

#include <map>
#include <thread>
#include <mutex>


static std::map<std::thread::id, Writer*> _installed;
static std::mutex _mutex;

std::string Writer::write(const Json::Value& json)
{
	std::ostringstream sstream;
	Writer* writer;
	try
	{
		writer = _installed.at(std::this_thread::get_id());
	}
	catch (const std::out_of_range&)
	{
		LOGW << "No writer installed in thread " << std::this_thread::get_id();
		return "";
	}
	writer->_writer->write(json, &sstream);
	return sstream.str();
}

Writer::Writer()
{
	Json::StreamWriterBuilder builder;
	builder["indentation"] = "";
	_writer.reset(builder.newStreamWriter());
}

void Writer::install()
{
	std::lock_guard<std::mutex> lock(_mutex);
	_installed[std::this_thread::get_id()] = this;
}

/* ######################### STATIC_WRITER_ENABLED  ######################### */
#endif
