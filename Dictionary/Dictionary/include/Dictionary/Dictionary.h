#ifndef DICTIONARY_DICTIONARY_H
#define DICTIONARY_DICTIONARY_H

#include "HashTable/HashTable-impl.h"

namespace puza {

class Dictionary : public HashTable<std::string, size_t>
{
public:
    explicit Dictionary(size_t capacity = DEFAULT_CAPACITY_);

    bool load(const char* filename);
    bool parse(const char* filename);

private:
    static std::string prepare_word(const std::string& word);
    static size_t lev_dist(const std::string& source, const std::string& target);
};

} // namespace puza

#endif // DICTIONARY_DICTIONARY_H