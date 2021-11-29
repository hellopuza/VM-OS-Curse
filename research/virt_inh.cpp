#include <benchmark/benchmark.h>

struct Base
{
    virtual ~Base() = default;
};

struct Derived : public Base
{};

struct VirtDerived : virtual public Base
{};

static void Virtual(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (size_t i = 0; i < state.range(); i++)
        {
            VirtDerived obj;
        }
    }
}
BENCHMARK(Virtual)->RangeMultiplier(2)->Range(1 << 22, 1 << 24)->Unit(benchmark::kMillisecond);

static void NonVirtual(benchmark::State& state)
{
    for (auto _ : state)
    {
        for (size_t i = 0; i < state.range(); i++)
        {
            Derived obj;
        }
    }
}
BENCHMARK(NonVirtual)->RangeMultiplier(2)->Range(1 << 22, 1 << 24)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();