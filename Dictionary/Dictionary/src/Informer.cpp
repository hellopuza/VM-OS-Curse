#include "Informer.h"

#include <algorithm>
#include <iostream>

namespace puza {

Informer::Informer(size_t max_words_num) : max_words_num_(max_words_num) {}

void Informer::appendWord(const std::string& word)
{
    std::string prepared = word;
    std::replace(prepared.begin(), prepared.end(), '\n', ' '), prepared.end();
    std::replace(prepared.begin(), prepared.end(), '\r', ' '), prepared.end();
    text_.push_back(prepared);

    if (text_.size() > max_words_num_)
    {
        text_.erase(text_.begin());
    }
}

void Informer::clearText()
{
    text_.clear();
}

void Informer::setMessage(const std::string& message)
{
    message_ = message;
}

void Informer::print() const
{
    std::cout << message_ << "\n\t";

    size_t text_len = 0;
    for (const auto& word : text_)
    {
        std::cout << word;
        text_len += word.length();
    }
    std::cout << "\n\t";

    for (size_t i = 0; i < text_len - text_.back().length(); i++)
    {
        std::cout << " ";
    }

    for (size_t i = 0; i < text_.back().length(); i++)
    {
        std::cout << "~";
    }
    std::cout << "\n\n";
}

} // namespace puza