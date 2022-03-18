#ifndef DICTIONARY_DICTIONARY_H
#define DICTIONARY_DICTIONARY_H

#include "HashTable/HashTable-impl.h"

namespace puza {

class Dictionary final : public HashTable<std::string, size_t>
{
public:
    explicit Dictionary(size_t capacity = DEFAULT_CAPACITY_);

    std::pair<std::string, size_t> findBestWord(const std::string& word);
};

} // namespace puza

#endif // DICTIONARY_DICTIONARY_H