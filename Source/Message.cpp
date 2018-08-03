#include "StdAfx.hpp"
#include "Message.hpp"


namespace Service
{
namespace Logging
{

Message::Message(MessageType type, const char* value)
	: stream(std::make_shared<Stream>(type))
{
	if(value != "")
	{
		stream->os << value << " ";
	}
}

Message::~Message()
{
	if(--stream->p < 0)
	{
		Logger::printMessage(stream->type, stream->os.str());
		stream->os.flush();
	}
}

Message& Message::operator<<(signed int value)
{
	stream->os << value << " ";
	return *this;
}

Message& Message::operator<<(uint value)
{
	stream->os << value << " ";
	return *this;
}

Message& Message::operator<<(signed long value)
{
	stream->os << value << " ";
	return *this;
}

Message& Message::operator<<(ulong value)
{
	stream->os << value << " ";
	return *this;
}

Message& Message::operator<<(float value)
{
	stream->os << value << " ";
	return *this;
}

Message& Message::operator<<(double value)
{
	stream->os << value << " ";
	return *this;
}

Message& Message::operator<<(const char* value)
{
	stream->os << value << " ";
	return *this;
}

Message& Message::operator<<(String& value)
{
	stream->os << value << " ";
	return *this;
}

} // namespace Logging
} // namespace Service