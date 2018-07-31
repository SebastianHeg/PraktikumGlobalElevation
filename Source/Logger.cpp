#include "StdAfx.hpp"
#include "Logger.hpp"

#include <fstream>
#include <sstream>
#include <cstdarg>


namespace Service
{
namespace Logging
{

Logger::Logger()
	: count(0)
{
}

Logger::~Logger()
{
}

void Logger::writeIntoNewFile(char* text)
{
	std::ostringstream path;
	path << "../../Logs/Log_" << count << ".log";
	while(true)
	{
		if(std::ifstream(path.str()))
		{
			count++;
			path << "../../Logs/Log_" << count << ".log";
			continue;
		}
		std::ofstream file(path.str());
		file << text << std::endl;
		file.close();
		break;
	}
}

void Logger::printMessage(MessageType type, const String& message)
{
	const char* types[] =
	{
		"[DEBUG]    ",
		"[INFO]     ",
		"[WARNING]  ",
		"[ERROR]    "
	};

	switch(type)
	{
		case MessageType::DebugMsg:
		std::cout << types[0];
		break;

		case MessageType::InfoMsg:
		std::cout << types[1];
		break;

		case MessageType::WarningMsg:
		std::cout << types[2];
		break;

		case MessageType::ErrorMsg:
		std::cout << types[3];
		break;
	}

	std::cout << message << std::endl;
}

Message Logger::debug(const char* value) const
{
	Message msg(MessageType::DebugMsg, value);

	return msg;
}

Message Logger::info(const char* value) const
{
	Message msg(MessageType::InfoMsg, value);

	return msg;
}

Message Logger::warning(const char* value) const
{
	Message msg(MessageType::WarningMsg, value);

	return msg;
}

Message Logger::error(const char* value) const
{
	Message msg(MessageType::ErrorMsg, value);

	return msg;
}

} // namespace Logging
} // namespace Service