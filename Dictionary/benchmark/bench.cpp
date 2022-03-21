#include "Dictionary/Dictionary.h"

#include <benchmark/benchmark.h>

#include <cstring>
#include <fstream>
#include <iostream>

constexpr size_t ITER_NUM = 100;
constexpr size_t MAX_THREADS_NUM = 1 << 10;

class TestClass
{
public:
    TestClass()
    {
        std::string filename("words.txt");
        std::ifstream file(filename);
        if (file.is_open())
        {
            std::string word;
            while (!file.eof())
            {
                file >> word;
                dict_[word]++;
            }
        }
        else
        {
            std::cout << filename << " not found\n";
            exit(-1);
        }
    }

    void findWord(const std::string& word, size_t threads_num)
    {
        dict_.findBestWord(word, 2, threads_num);
    }

private:
    puza::Dictionary dict_;
};

TestClass test;

static void SingleThread(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (size_t i = 0; i < ITER_NUM; i++)
        {
            test.findWord("hashtable", 1);
        }
    }
}
BENCHMARK(SingleThread)->Unit(benchmark::kMillisecond);

static void Paralleling(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (size_t i = 0; i < ITER_NUM; i++)
        {
            test.findWord("hashtable", state.range());
        }
    }
}
BENCHMARK(Paralleling)->DenseRange(2, MAX_THREADS_NUM, 1)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();