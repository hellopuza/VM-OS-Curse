#include "Dictionary/Corrector.h"
#include "StringUtils.h"

#include <cstring>
#include <fstream>
#include <vector>

namespace puza {

template<>
Hash& Hash::operator()(const size_t& data)
{
    return *this = Hash(data);
}

Corrector::Corrector(size_t dict_num) : dicts_(dict_num), info_(5) {}

bool Corrector::load(const char* filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string word;
        while (!file.eof())
        {
            file >> word;
            word = prepare_word(word);
            if (word.length() >= MIN_WORD_LEN_)
            {
                dicts_[word.length() - MIN_WORD_LEN_][word]++;
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool Corrector::parse(const char* filename)
{
    if (text_.load(filename))
    {
        for (const auto& text_it : text_)
        {
            std::string word = prepare_word(text_it.current_word());
            info_.appendWord(text_it.current_section());
            
            if ((word.length() >= MIN_WORD_LEN_) && !(dicts_[word.length() - MIN_WORD_LEN_].contains(word)))
            {
                correct(text_it);
            }
        }

        text_.save(filename);
    }
    else
    {
        return false;
    }

    return true;
}

void Corrector::correct(const TextEditor::iterator& text_it)
{
    std::string word = prepare_word(text_it.current_word());

    for (int delta_len = -1; delta_len < 2; delta_len++)
    {
        auto word_len = static_cast<int>(word.length() - MIN_WORD_LEN_) + delta_len;
        for (const auto& dict_it : dicts_[static_cast<size_t>(word_len)])
        {
            if (lev_dist(word, dict_it.value.first) < 3)
            {
                text_.replace(text_it, dict_it.value.first);

                info_.setMessage("Corrected to " + dict_it.value.first);
                info_.print();
                return;
            }
        }
    }

    info_.setMessage("Unknown word");
    info_.print();
}

} // namespace puza