#include <benchmark/benchmark.h>
#include <spdlog/spdlog.h>
#include <iostream>

static void BM_solver(benchmark::State& state) {
    int i = 0;
    for (auto _ : state) {
        // spdlog::info("Hello, {}!", i++);
        std::cout << "Hello, " << i++ << "!" << std::endl;
    }
}

// ベンチマーク関数を登録
BENCHMARK(BM_solver);

// メイン関数
BENCHMARK_MAIN();