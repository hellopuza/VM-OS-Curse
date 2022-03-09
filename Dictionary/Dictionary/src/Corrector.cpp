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

void Corrector::setMode(int mode)
{
    mode_ = mode;
}

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

bool Corrector::process(const char* filename)
{
    if (text_.load(filename))
    {
        parseText();
        text_.save(filename);
    }
    else
    {
        return false;
    }

    return true;
}

void Corrector::parseText()
{
    for (const auto& text_it : text_)
    {
        std::string word = prepare_word(text_it.current_word());

        if (mode_ == OUTPUT)
        {
            info_.appendWord(text_it.current_section());
        }
            
        if ((word.length() >= MIN_WORD_LEN_) && !(dicts_[word.length() - MIN_WORD_LEN_].contains(word)))
        {
            correctWord(text_it, word);
        }
    }
}

void Corrector::correctWord(const TextEditor::iterator& text_it, const std::string& word)
{
    for (int delta_len = -1; delta_len < 2; delta_len++)
    {
        auto word_len = static_cast<int>(word.length() - MIN_WORD_LEN_) + delta_len;
        for (const auto& dict_it : dicts_[static_cast<size_t>(word_len)])
        {
            if (lev_dist(word, dict_it.value.first) < 3)
            {
                text_.replace(text_it, dict_it.value.first);

                if (mode_ == OUTPUT)
                {
                    info_.setMessage("Corrected to " + dict_it.value.first);
                    info_.print();
                }
                return;
            }
        }
    }

    if (mode_ == OUTPUT)
    {
        info_.setMessage("Unknown word");
        info_.print();
    }
}

} // namespace puza