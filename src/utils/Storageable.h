#ifndef sergomor_Storageable_h
#define sergomor_Storageable_h

#include "Serializable.h"
#include "Streambuff.h"
#include <FS.h>

namespace sergomor
{

template <typename T, const char *filename>
class Storageable : public Serializable<T>
{
public:
	bool load();
	bool save();
	bool exists();
};

template <typename T, const char *filename>
bool Storageable<T, filename>::load()
{
	bool res;
	SPIFFS.begin();
	File file = SPIFFS.open(filename, "r");
	if (res = (bool)file)
	{
		size_t len = file.size();
		uint8_t buf[len];
		file.read(buf, len);
		file.close();
		IStreambuff is(buf, len);
		is >> (T &)(*this);
	}
	return res;
}

template <typename T, const char *filename>
bool Storageable<T, filename>::save()
{
	bool res;
	SPIFFS.begin();
	File file = SPIFFS.open(filename, "w");
	if (res = (bool)file)
	{
		size_t len = this->length();
		uint8_t buf[len];
		OStreambuff os(buf, len);
		os << (T &)(*this);
		file.write(buf, len);
		file.close();
	}
	return res;
}

template <typename T, const char *filename>
bool Storageable<T, filename>::exists()
{
	return SPIFFS.begin() ? SPIFFS.exists(filename) : false;
}

}; // namespace sergomor
#endif