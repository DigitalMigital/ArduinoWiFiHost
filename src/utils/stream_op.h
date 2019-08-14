#ifndef sergomor_stream_op_h
#define sergomor_stream_op_h

#include <Arduino.h>

#define endl '\n'

template <class T>
inline Print &operator<<(Print &obj, T arg)
{
	obj.print(arg);
	return obj;
}

struct DebugStream
{
	template <typename T>
	Print &operator<<(const T &arg) const
	{
		return Serial << "debug " << arg;
	}
};

// This type also provides a stream-like interface but does nothing
struct NoStream
{
	template <class T>
	const NoStream &operator<<(const T &arg) const
	{
		return *this;
	}
};

#ifdef DEBUG
extern DebugStream debug;
#else
extern NoStream debug;
#endif

#endif