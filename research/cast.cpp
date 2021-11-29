#include <benchmark/benchmark.h>

struct Base
{
    virtual ~Base() = default;
};

struct Derived : public Base
{};

static void Dynamic(benchmark::State& state)
{
    auto* derived = new Derived;
    auto* base = static_cast<Base*>(derived);
    for (auto _ : state)
    {
        for (size_t i = 0; i < state.range(); i++)
        {
            derived = dynamic_cast<Derived*>(base);
        }
    }
    delete derived;
}
BENCHMARK(Dynamic)->RangeMultiplier(2)->Range(1 << 22, 1 << 24)->Unit(benchmark::kMillisecond);

static void Static(benchmark::State& state)
{
    auto* derived = new Derived;
    Base* base = static_cast<Base*>(derived);
    for (auto _ : state)
    {
        for (size_t i = 0; i < state.range(); i++)
        {
            derived = static_cast<Derived*>(base);
        }
    }
    delete derived;
}
BENCHMARK(Static)->RangeMultiplier(2)->Range(1 << 22, 1 << 24)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();