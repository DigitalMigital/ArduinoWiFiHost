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

struct NoStream
{
	template <class T>
	const NoStream &operator<<(const T &arg) const
	{
		return *this;
	}
};

#define DEBUG

#ifdef DEBUG
#define debug Serial
#else
extern NoStream debug;
#endif

#endif