#pragma once
#include <chrono>
#include "common/namespace_macro.hpp"

BEGIN_SOLVER_NAMESPACE

class TaskTimer {
public:
    TaskTimer() = default;
    TaskTimer(const TaskTimer&) = delete;
    TaskTimer& operator=(const TaskTimer&) = delete;

    ~TaskTimer() = default;

    void start();
    void stop();
    double elapsed_s();
private:
    std::chrono::high_resolution_clock::time_point start_time_s;
    std::chrono::high_resolution_clock::time_point end_time_s;
};

END_SOLVER_NAMESPACE
