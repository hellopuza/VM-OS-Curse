#ifndef DICTIONARY_DICTIONARY_H
#define DICTIONARY_DICTIONARY_H

#include "HashTable/HashTable-impl.h"

#include <vector>

namespace puza {

class Dictionary final : public HashTable<std::string, size_t>
{
public:
    explicit Dictionary(size_t capacity = DEFAULT_CAPACITY_);
    Dictionary(const Dictionary& obj) = default;
    Dictionary(Dictionary&& obj) noexcept = default;
    ~Dictionary() = default;

    Dictionary& operator=(const Dictionary &obj) = default;
    Dictionary& operator=(Dictionary&& obj) noexcept = default;

    std::string findBestWord(const std::string& word, size_t max_lev_dist, size_t threads_num = 1);

private:
    std::string findBestWordParallel(const std::string& word, size_t max_lev_dist, size_t threads_num);
};

} // namespace puza

#endif // DICTIONARY_DICTIONARY_H