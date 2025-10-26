#include "util/timer.hpp"
#include <chrono>
#include "common/namespace_macro.hpp"

BEGIN_SOLVER_NAMESPACE

void TaskTimer::start() {
    this->start_time_s = std::chrono::high_resolution_clock::now();
}

void TaskTimer::stop() {
    this->end_time_s = std::chrono::high_resolution_clock::now();
}

double TaskTimer::elapsed_s() {
    std::chrono::duration<double> execution_time_s = this->end_time_s - this->start_time_s;
    return execution_time_s.count();
}

END_SOLVER_NAMESPACE
