#ifndef sergomor_Streambuff_h
#define sergomor_Streambuff_h

#include "List.h"
#include "stream_op.h"
#include <Arduino.h>

#define STREAMBUFF_BUFF_SIZE 200

namespace sergomor
{

class Streambuff
{
public:
	Streambuff(uint8_t *, size_t);
	Streambuff(){};
	void init(uint8_t *, size_t);

	inline size_t length() { return len; }
	inline uint8_t *data() { return buf; }

protected:
	uint8_t *buf = nullptr;
	size_t len = 0;
	size_t pos = 0;
};

class OStreambuff : public Streambuff
{
public:
	OStreambuff(uint8_t *buf, size_t len) : Streambuff(buf, len) {}
	OStreambuff() : Streambuff(){};
	template <typename T>
	OStreambuff &operator<<(T &data)
	{
		copyData(data);
		return *this;
	}
	template <typename T>
	OStreambuff &operator<<(List<T &> list)
	{
		auto i = list.begin();
		while (i != list.end())
			*this << *i;
		return *this;
	}
	OStreambuff &operator<<(String &);
	OStreambuff &operator<<(const char *);

private:
	template <typename T>
	void copyData(T &data)
	{
		if (pos + sizeof(T) <= len)
		{
			memcpy(buf + pos, &data, sizeof(T));
			pos += sizeof(T);
		}
	}
	void copyString(const String &);
};

class IStreambuff : public Streambuff
{
public:
	IStreambuff(uint8_t *buf, size_t len) : Streambuff(buf, len) {}
	IStreambuff() : Streambuff(){};
	template <typename T>
	IStreambuff &operator>>(T &data)
	{
		copyData(data);
		return *this;
	}
	template <typename T>
	IStreambuff &operator>>(List<T &> list)
	{
		auto i = list.begin();
		while (i != list.end())
			*this >> *i;
		return *this;
	}
	IStreambuff &operator>>(String &);

private:
	template <typename T>
	void copyData(T &data)
	{
		memcpy(&data, buf + pos, sizeof(T));
		pos += sizeof(T);
	}
};

class DataStream
{
public:
	DataStream() {}
	DataStream(uint8_t *buf, size_t len) { init(buf, len); }
	void init(uint8_t *buf, size_t len)
	{
		os.init(buf, len);
		is.init(buf, len);
	}

	template <typename T>
	DataStream &operator<<(T &t)
	{
		os << t;
		return *this;
	}
	template <typename T>
	DataStream &operator>>(T &t)
	{
		is >> t;
		return *this;
	}

private:
	OStreambuff os;
	IStreambuff is;
};
}; // namespace sergomor
#endif