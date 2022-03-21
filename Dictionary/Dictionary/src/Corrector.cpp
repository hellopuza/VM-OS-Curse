#include "Dictionary/Corrector.h"
#include "Text/StringUtils.h"

#include <cstring>
#include <fstream>
#include <iostream>

namespace puza {

Corrector::Corrector(size_t dict_num) : dicts_(dict_num), info_(INFORMER_WORDS_NUM_) {}

void Corrector::setMode(int mode)
{
    process_mode_ = mode;
}

void Corrector::setParallel(bool parallel)
{
    parallel_processing_ = parallel;
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
        if (parallel_processing_)
        {
            for (auto& dict : dicts_)
            {
                dict.value.makeTraversalArray();
            }
        }
        parseText();

        if (process_mode_ != NO_CORRECTION)
        {
            text_.save(filename);
        }

        std::cout << info_output_;
        info_output_.clear();
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
            std::vector<std::string> best_words;
            size_t dict_id = word.length() - MIN_WORD_LEN_;
            if (word.length() > MIN_WORD_LEN_)
            {
                best_words.push_back(dicts_[dict_id - 1].findBestWord(word, MAX_LEV_DIST_, parallel_processing_));
            }

            best_words.push_back(dicts_[dict_id].findBestWord(word, MAX_LEV_DIST_, parallel_processing_));
            best_words.push_back(dicts_[dict_id + 1].findBestWord(word, MAX_LEV_DIST_, parallel_processing_));

            updateOutput(best_words, &text_it);
        }
    }
}

void Corrector::updateOutput(const std::vector<std::string>& best_words, TextEditor::iterator* text_it)
{
    if (best_words[1].length() != 0)
    {
        if (process_mode_ != NO_CORRECTION)
        {
            text_.replace(*text_it, best_words[1]);
            if (process_mode_ != NO_OUTPUT)
            {
                info_.setMessage("Corrected to " + best_words[1]);
                info_output_ += info_.getOutput();
            }
        }
        else
        {
            std::string message("Found best words:");
            for (const auto& word : best_words)
            {
                message += " " + word;
            }
            info_.setMessage(message);
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

} // namespace puza