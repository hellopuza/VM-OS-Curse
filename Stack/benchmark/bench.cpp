#include <benchmark/benchmark.h>
#include "Stack/Stack-impl.h"

const size_t kIterNum = 1 << 24;

static void Grow_Factor(benchmark::State& state)
{
    for (auto _ : state)
    {
        puza::Stack<int> stk(static_cast<float>(state.range()) / 10.0F);
        for (size_t i = 0; i < kIterNum; i++)
        {
            stk.push(1);
        }
    }
}
BENCHMARK(Grow_Factor)->DenseRange(11, 21, 1)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();