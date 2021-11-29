#include <benchmark/benchmark.h>

struct ISquare
{
    virtual ~Square() = default;
    virtual float vsquare() const = 0;
};

struct Rectangle : public ISquare
{
    float a = 0;
    float b = 0;

    float vsquare() const override
    {
        return a * b;
    }

    float square() const
    {
        return a * b;
    }
};

static void Virtual(benchmark::State& state)
{
    auto* rect = new Rectangle;
    ISquare* sqr = rect;
    for (auto _ : state)
    {
        for (size_t i = 0; i < state.range(); i++)
        {
            sqr->vsquare();
        }
    }
    delete rect;
}
BENCHMARK(Virtual)->RangeMultiplier(2)->Range(1 << 25, 1 << 27)->Unit(benchmark::kMillisecond);

static void NonVirtual(benchmark::State& state)
{
    auto* rect = new Rectangle;
    for (auto _ : state)
    {
        for (size_t i = 0; i < state.range(); i++)
        {
            rect->square();
        }
    }
    delete rect;
}
BENCHMARK(NonVirtual)->RangeMultiplier(2)->Range(1 << 25, 1 << 27)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();