#include "Dictionary/Dictionary.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

namespace puza {

template <>
Hash Hash::operator()(const std::string& data) const
{
    return sum(data.c_str(), strlen(data.c_str()));
}

Dictionary::Dictionary(size_t capacity) : HashTable(capacity)
{}

bool Dictionary::load(const char* filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string word;
        while (!file.eof())
        {
            file >> word;
            word = prepare_word(word);
            if (word.length() > 1)
            {
                (*this)[word]++;
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool Dictionary::parse(const char* filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();

        std::string file_content(buffer.str());
        size_t begin = 0;
        size_t end = 0;
        std::cout << file_content.length() << "\n";
        while (end < file_content.length())
        {
            std::string word;
            while ((!isalpha(file_content[end])) && (end < file_content.length()))
            {
                end++;
            }
            begin = end;

            while ((isalpha(file_content[end])) && (end < file_content.length()))
            {
                word.push_back(file_content[end]);
                end++;
            }
            std::cout << word << "\n";
            if (word.length() > 1)
            {
                if (!find(word))
                {
                    bool corrected = false;
                    for (const auto& it : *this)
                    {
                        if (lev_dist(word, it.value.first) < 3)
                        {
                            std::cout << word << "->" << it.value.first << "\n";
                            file_content.replace(begin, end - begin, it.value.first);
                            corrected = true;
                            break;
                        }
                    }
                    if (!corrected)
                    {
                        std::cout << "not corrected " << word << "\n";
                    }
                }
            }
        }

        std::ofstream out(filename);
        out << file_content;
    }
    else
    {
        return false;
    }

    return true;
}

std::string Dictionary::prepare_word(const std::string& word)
{
    std::string res;
    for (const auto& c: word)
    {
        res.push_back(static_cast<char>(tolower(c)));
    }

    while (!isalpha(res.back()))
    {
        res.pop_back();
    }
    return res;
}

size_t Dictionary::lev_dist(const std::string& source, const std::string& target)
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