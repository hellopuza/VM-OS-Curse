#include "Dictionary/Corrector.h"
#include "Text/StringUtils.h"
#include "ThreadPool.h"

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

bool Corrector::load_text(const char* filename)
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

bool Corrector::load_data(const char* filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string word;
        size_t freq;
        while (!file.eof())
        {
            file >> word >> freq;
            dicts_[word.length() - MIN_WORD_LEN_][word] += freq;
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool Corrector::save_data(const char* filename) const
{
    std::ofstream file(filename, std::ofstream::out);
    if (file.is_open())
    {
        for (const auto& dict : dicts_)
        {
            for (const auto& node : dict.value)
            {
                file << node.key << " " << node.value << "\n";
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
        for (auto& dict : dicts_)
        {
            dict.value.setThreadsNum(parallel_processing_ ? std::thread::hardware_concurrency() : 1);
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
            const size_t dicts_num = 3;
            std::vector<std::string*> best_words(dicts_num);
            size_t dict_id = word.length() - MIN_WORD_LEN_;

            auto process = [&](size_t vec_ind, size_t dict_ind) -> void
            {
                best_words[vec_ind] = dicts_[dict_ind].findBestWord(word, MAX_LEV_DIST_);
            };

            ThreadPool thpool(dicts_num);
            if (word.length() > MIN_WORD_LEN_)
            {
                thpool.create_task(process, 0, dict_id - 1);
            }

            thpool.create_task(process, 1, dict_id);
            thpool.create_task(process, 2, dict_id + 1);
            thpool.join();

            updateOutput(best_words, &text_it);
        }
    }
}

void Corrector::updateOutput(const std::vector<std::string*>& best_words, TextEditor::iterator* text_it)
{
    if (best_words[1] && (best_words[1]->length() != 0))
    {
        if (process_mode_ != NO_CORRECTION)
        {
            text_.replace(*text_it, *best_words[1]);
            if (process_mode_ != NO_OUTPUT)
            {
                info_.setMessage("Corrected to " + *best_words[1]);
                info_output_ += info_.getOutput();
            }
        }
        else
        {
            std::string message("Found best words:");
            for (const auto& word : best_words)
            {
                if (word)
                {
                    message += " " + *word;
                }
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