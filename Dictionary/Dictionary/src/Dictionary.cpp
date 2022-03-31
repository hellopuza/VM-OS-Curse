#include "Dictionary/Dictionary.h"
#include "Text/StringUtils.h"
#include "ThreadPool.h"

namespace puza {

Dictionary::Dictionary(size_t capacity) : HashTable(capacity) {}

void Dictionary::setThreadsNum(size_t threads_num)
{
    threads_num_ = threads_num;
}

size_t Dictionary::getThreadsNum() const
{
    return threads_num_;
}

std::string* Dictionary::findBestWord(const std::string& word, size_t max_lev_dist) const
{
    if (threads_num_ > 1)
    {
        return findBestWordParallel(word, max_lev_dist);
    }

    std::string* best_word = nullptr;
    size_t min_lev_dist = max_lev_dist;
    size_t max_freq = 0;

    for (const auto& dict_it : *this)
    {
        size_t ld = lev_dist(word, dict_it.key);
        if ((ld <= min_lev_dist) && (dict_it.value > max_freq))
        {
            max_freq = dict_it.value;
            best_word = const_cast<std::string*>(&dict_it.key);
            min_lev_dist = ld;
        }
    }

    return best_word;
}

std::string* Dictionary::findBestWordParallel(const std::string& word, size_t max_lev_dist) const
{
    const size_t piece_len = size() / threads_num_;

    struct WordInfo
    {
        std::string* word = nullptr;
        size_t min_lev_dist;
        size_t max_freq = 0;
    };
    std::vector<WordInfo> best_words(threads_num_);
    for (auto& winfo : best_words)
    {
        winfo.min_lev_dist = max_lev_dist;
    }

    auto check = [&](const Node* node, WordInfo* winfo) -> void
    {
        size_t ld = lev_dist(word, node->key);
        if ((ld <= winfo->min_lev_dist) && (node->value > winfo->max_freq))
        {
            winfo->word = const_cast<std::string*>(&node->key);
            winfo->min_lev_dist = ld;
            winfo->max_freq = node->value;
        }
    };

    auto process = [&](size_t begin, WordInfo* winfo) -> void
    {
        for (size_t i = begin; (i < size()) && (i - begin < piece_len); i++)
        {
            check(iter_vec_[i], winfo);
        }
    };

    ThreadPool thpool(threads_num_);
    for (size_t i = 0; i < threads_num_; i++)
    {
        thpool.create_task(process, i * piece_len, &best_words[i]);
    }
    thpool.join();

    WordInfo winfo;
    bool finding_word = true;
    for (size_t i = 0; i < threads_num_; i++)
    {
        if (finding_word && best_words[i].word)
        {
            winfo = best_words[i];
            finding_word = false;
        }
        if (!winfo.word || !best_words[i].word)
        {
            continue;
        }

        size_t ld = lev_dist(*winfo.word, *best_words[i].word);
        if ((ld <= winfo.min_lev_dist) && (best_words[i].max_freq > winfo.max_freq))
        {
            winfo.word = best_words[i].word;
            winfo.min_lev_dist = ld;
            winfo.max_freq = best_words[i].max_freq;
        }
    }

    return winfo.word;
}

} // namespace puza