#include "Dictionary/Dictionary.h"
#include "Text/StringUtils.h"
#include "ThreadPool.h"

namespace puza {

Dictionary::Dictionary(size_t capacity) : HashTable(capacity) {}

void Dictionary::makeTraversalArray()
{
    elements_.clear();
    for (auto& dict_it : *this)
    {
        elements_.push_back(&dict_it);
    }
}

std::string Dictionary::findBestWord(const std::string& word, size_t max_lev_dist, bool parallel)
{
    if (parallel)
    {
        return findBestWordParallel(word, max_lev_dist);
    }

    std::string best_word;
    size_t min_lev_dist = max_lev_dist;
    size_t max_freq = 0;

    for (const auto& dict_it : *this)
    {
        size_t ld = lev_dist(word, dict_it.key);
        if ((ld < max_lev_dist) && (dict_it.value > max_freq) && (ld <= min_lev_dist))
        {
            max_freq = dict_it.value;
            best_word = dict_it.key;
            min_lev_dist = ld;
        }
    }

    return best_word;
}

std::string Dictionary::findBestWordParallel(const std::string& word, size_t max_lev_dist)
{
    const size_t threads_num = std::thread::hardware_concurrency();
    const size_t piece_len = size() / threads_num;

    const size_t max_levdist = 10;
    struct WordInfo
    {
        std::string best_word;
        size_t min_lev_dist = max_levdist;
        size_t max_freq = 0;
    };
    std::vector<WordInfo> best_words(threads_num);

    {
        ThreadPool thpool(threads_num);

        auto check = [&](const Node& node, WordInfo& winfo) -> void
        {
            size_t ld = lev_dist(word, node.key);
            if ((ld <= max_lev_dist) && (node.value > winfo.max_freq) && (ld <= winfo.min_lev_dist))
            {
                winfo.best_word = node.key;
                winfo.min_lev_dist = ld;
                winfo.max_freq = node.value;
            }
        };

        auto process = [&](size_t begin, WordInfo& winfo) -> void
        {
            for (size_t i = begin; (i + begin < size()) && (i < piece_len); i++)
            {
                check(*elements_[i], winfo);
            }
        };

        for (size_t i = 0; i < threads_num; i++)
        {
            thpool.create_task(process, i, best_words[i]);
        }
    }

    WordInfo winfo;
    for (size_t i = 0; i < threads_num; i++)
    {
        size_t ld = lev_dist(winfo.best_word, best_words[i].best_word);
        if ((ld <= max_lev_dist) && (best_words[i].max_freq > winfo.max_freq) && (ld <= winfo.min_lev_dist))
        {
            winfo.best_word = best_words[i].best_word;
            winfo.min_lev_dist = ld;
            winfo.max_freq = best_words[i].max_freq;
        }
    }

    return winfo.best_word;
}

} // namespace puza