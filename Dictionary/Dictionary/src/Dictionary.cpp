#include "Dictionary/Dictionary.h"
#include "StringUtils.h"

namespace puza {

template<>
Hash& Hash::operator()(const std::string& data)
{
    return (*this)(data.c_str(), data.length());
}

Dictionary::Dictionary(size_t capacity) : HashTable(capacity) {}

std::pair<std::string, size_t> Dictionary::findBestWord(const std::string& word)
{
    std::string best_word;
    size_t max_freq = 0;

    for (const auto& dict_it : *this)
    {
        if (lev_dist(word, dict_it.value.first) < 3)
        {
            if (dict_it.value.second > max_freq)
            {
                max_freq = dict_it.value.second;
                best_word = dict_it.value.first;
            }
        }
    }

    return std::make_pair(best_word, max_freq);
}

} // namespace puza