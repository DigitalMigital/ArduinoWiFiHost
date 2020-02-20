#pragma once
#include <map>
#include "Storageable.h"

namespace sergomor
{

class StorageableMap : public StorageableT<StorageableMap>
{
public:
	virtual std::map<String, String> map() = 0;
	virtual void unmap(std::map<String, String> &) = 0;
	// Serializable
	virtual size_t length();
	virtual OStreambuff &output(OStreambuff &os);
	virtual IStreambuff &input(IStreambuff &is);
};

}; // namespace sergomor
