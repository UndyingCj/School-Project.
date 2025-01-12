#include "Timer.h"

void Timer::startTimer()
{
    start = std::chrono::steady_clock::now();
}

double Timer::stopTimer()
{
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}
