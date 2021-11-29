#include "Queue/Queue-impl.h"

#include <benchmark/benchmark.h>

static void QueuePushing(benchmark::State& state)
{
    for (auto _ : state)
    {
        puza::Queue<int> queue;
        for (size_t i = 0; i < state.range(); i++)
        {
            queue.push(1);
        }
    }
}
BENCHMARK(QueuePushing)->RangeMultiplier(2)->Range(1 << 20, 1 << 24)->Unit(benchmark::kMillisecond);

static void QueuePushAndPop(benchmark::State& state)
{
    for (auto _ : state)
    {
        puza::Queue<int> queue;
        for (size_t i = 0; i < state.range(); i++)
        {
            queue.push(1);
            queue.push(1);
            queue.pop();
        }
    }
}
BENCHMARK(QueuePushAndPop)->RangeMultiplier(2)->Range(1 << 20, 1 << 24)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();