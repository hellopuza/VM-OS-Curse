#include "StringUtils.h"

#include <vector>

namespace puza {

std::string prepare_word(const std::string& word)
{
    if (isupper(word[0]))
    {
        return std::string();
    }

    std::string res;
    for (const auto& c : word)
    {
        res.push_back(static_cast<char>(tolower(c)));
    }

    while ((res.length() > 0) && !isalpha(res.back()))
    {
        res.pop_back();
    }

    return res;
}

size_t lev_dist(const std::string& source, const std::string& target)
{
    if (source.size() > target.size())
    {
        return lev_dist(target, source);
    }

    size_t min_size = source.size();
    size_t max_size = target.size();
    std::vector<size_t> lev_dist(min_size + 1);

    for (size_t i = 0; i <= min_size; ++i)
    {
        lev_dist[i] = i;
    }

    for (size_t j = 1; j <= max_size; ++j)
    {
        size_t previous_diagonal = lev_dist[0];
        size_t previous_diagonal_save = 0;
        lev_dist[0]++;

        for (size_t i = 1; i <= min_size; ++i)
        {
            previous_diagonal_save = lev_dist[i];
            if (source[i - 1] == target[j - 1])
            {
                lev_dist[i] = previous_diagonal;
            }
            else
            {
                lev_dist[i] = std::min(std::min(lev_dist[i - 1], lev_dist[i]), previous_diagonal) + 1;
            }
            previous_diagonal = previous_diagonal_save;
        }
    }

    return lev_dist[min_size];
}

} // namespace puza