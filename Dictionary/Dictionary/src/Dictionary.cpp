#include "Dictionary/Dictionary.h"

namespace puza {

template<>
Hash& Hash::operator()(const std::string& data)
{
    return (*this)(data.c_str(), data.length());
}

Dictionary::Dictionary(size_t capacity) : HashTable(capacity) {}

} // namespace puza