#include "StorageableMap.h"

namespace sergomor
{
size_t StorageableMap::length()
{
    std::map<String, String> data = map();
    size_t size = 0;
    for (auto v = data.begin(); v != data.end(); v++)
        size += sizeof(size_t) + v->first.length() + v->second.length() + 2;
    return size;
}

OStreambuff &StorageableMap::output(OStreambuff &os)
{
    std::map<String, String> data = map();
    String key, val;
    size_t size = data.size();
    //debug << "save size: " << size << endl;
    os << size;
    for (auto v = data.begin(); v != data.end(); v++)
    {
        key = v->first;
        val = v->second;
        os << key << val;
        //debug << "SAVE Key: " << key << " Val: " << val << endl;
    }
    return os;
}

IStreambuff &StorageableMap::input(IStreambuff &is)
{
    std::map<String, String> data;
    String key, val;
    size_t size;
    is >> size;
    //debug << "load size: " << size << endl;
    for (auto i = 0; i < size; i++)
    {
        is >> key >> val;
        //debug << "LOAD Key: " << key << " Val: " << val << endl;
        data.insert(std::make_pair(key, val));
    }
    unmap(data);
    return is;
}

} // namespace sergomor