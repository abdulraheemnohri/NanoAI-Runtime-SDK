#ifndef NANOAI_BENCHMARK_SUITE_H
#define NANOAI_BENCHMARK_SUITE_H

namespace nanoai {
namespace benchmark {

class BenchmarkSuite {
public:
    static void runAll();
    static void benchmarkLatency();
    static void benchmarkThroughput();
};

} }
#endif
