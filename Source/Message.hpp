#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <sstream>


namespace Service
{
namespace Logging
{

class Message
{
public:
	Message(MessageType type, const char* value);
	~Message();

public:
	Message& operator << (signed int value);
	Message& operator << (uint value);
	Message& operator << (signed long value);
	Message& operator << (ulong value);
	Message& operator << (float value);
	Message& operator << (double value);
	Message& operator << (const char* value);
	Message& operator << (String& value);

private:
	struct Stream
	{
		Stream(MessageType t)
			: type(t), p(1)
		{
		}
		int p;
		std::ostringstream os;
		MessageType type;
	};
	std::shared_ptr<Stream> stream;

private:
	friend class Logger;
};

} // namespace Logging
} // namespace Service

#endif