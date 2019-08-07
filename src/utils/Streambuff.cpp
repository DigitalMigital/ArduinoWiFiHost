#include "Streambuff.h"
//#include "Serializable.h"

namespace sergomor
{

Streambuff::Streambuff(uint8_t *_buf, size_t _size)
{
	init(_buf, _size);
}

void Streambuff::init(uint8_t *_buf, size_t _size)
{
	buf = _buf;
	len = _size;
	pos = 0;
}

/////////////////
// OStreambuff //
/////////////////

void OStreambuff::copyString(const String &string)
{
	if (pos + string.length() < len)
	{
		memcpy(buf + pos, string.c_str(), string.length());
		pos += string.length();
		buf[pos++] = NULL;
	}
}

OStreambuff &OStreambuff::operator<<(String &string)
{
	copyString(string);
	return *this;
}

OStreambuff &OStreambuff::operator<<(const char *cstr)
{
	String s(cstr);
	return *this << s;
}

/////////////////
// IStreambuff //
/////////////////

IStreambuff &IStreambuff::operator>>(String &string)
{
	string = String((char *)(buf + pos));
	pos += string.length() + 1;
	return *this;
}

/*
////////////////
// DataStream //
////////////////

DataStream::DataStream(uint8_t* buf, size_t len)
{
	init(buf, len);
}

void DataStream::init(uint8_t* buf, size_t len)
{
	os.init(buf, len);
	is.init(buf, len);
}
*/
} // namespace sergomor