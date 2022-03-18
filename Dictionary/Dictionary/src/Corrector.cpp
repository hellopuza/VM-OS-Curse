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
    process_mode_ = mode;
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
        info_output_.clear();

        parseText();

        if (process_mode_ != NO_CORRECTION)
        {
            text_.save(filename);
        }

        std::cout << info_output_;
    }
    else
    {
        return false;
    }

    return true;
}

void Corrector::parseText()
{
    for (auto text_it = text_.begin(); text_it != text_.end(); text_it.next())
    {
        std::string word = prepare_word(text_it.current_word());

        if (process_mode_ != NO_OUTPUT)
        {
            info_.appendWord(text_it.current_section());
        }
            
        if ((word.length() >= MIN_WORD_LEN_) && !(dicts_[word.length() - MIN_WORD_LEN_].contains(word)))
        {
            std::string right_word;
            size_t max_freq = 0;
            for (int delta_len = -1; delta_len < 2; delta_len++)
            {
                auto word_len = static_cast<int>(word.length() - MIN_WORD_LEN_) + delta_len;
                std::pair<std::string, size_t> best_word = dicts_[static_cast<size_t>(word_len)].findBestWord(word);

                if (best_word.second > max_freq)
                {
                    right_word = best_word.first;
                    max_freq = best_word.second;
                }
            }

            if (right_word.length() != 0)
            {
                if (process_mode_ != NO_CORRECTION)
                {
                    text_.replace(text_it, right_word);
                    if (process_mode_ != NO_OUTPUT)
                    {
                        info_.setMessage("Corrected to " + right_word);
                        info_output_ += info_.getOutput();
                    }
                }
                else
                {
                    info_.setMessage("Found best word " + right_word);
                    info_output_ += info_.getOutput();
                }

            }
            else
            {
                if (process_mode_ != NO_OUTPUT)
                {
                    info_.setMessage("Unknown word");
                    info_output_ += info_.getOutput();
                }
            }
        }
    }
}

} // namespace puza