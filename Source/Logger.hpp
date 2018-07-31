#ifndef LOGGER_HPP
#define LOGGER_HPP

namespace Service
{
namespace Logging
{

class Message;

enum class MessageType
{
	DebugMsg, InfoMsg, WarningMsg, ErrorMsg
};


class Logger
{
public:
	Logger();
	~Logger();

public:
	Message debug(const char* value = "") const;
	Message info(const char* value = "") const;
	Message warning(const char* value = "") const;
	Message error(const char* value = "") const;

	static void printMessage(MessageType type, const String& message);
	void writeIntoNewFile(char* text);

private:
	int count;
};


#define logDebug Service::Logging::Logger().debug
#define logInfo Service::Logging::Logger().info
#define logWarning Service::Logging::Logger().warning
#define logError Service::Logging::Logger().error

} // namespace Logging
} // namespace Service

#endif