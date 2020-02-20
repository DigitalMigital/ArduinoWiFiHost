#ifndef sergomor_Storageable_h
#define sergomor_Storageable_h

#include "Serializable.h"
#include <FS.h>

#if defined(ESP32)
#include <SPIFFS.h>
#endif

namespace sergomor
{

template <typename T>
class StorageableT : public Serializable<T>
{
public:
	bool load(const char *);
	bool save(const char *);
	bool exists(const char *);
};

template <typename T>
bool StorageableT<T>::load(const char *filename)
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

template <typename T>
bool StorageableT<T>::save(const char *filename)
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

template <typename T>
bool StorageableT<T>::exists(const char *filename)
{
	return SPIFFS.begin() ? SPIFFS.exists(filename) : false;
}

template <typename T, const char *filename>
class Storageable : public StorageableT<T>
{
public:
	bool load() { return StorageableT<T>::load(filename); }
	bool save() { return StorageableT<T>::save(filename); }
	bool exists() { return StorageableT<T>::exists(filename); }
};

}; // namespace sergomor
#endif