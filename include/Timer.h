#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
private:
    std::chrono::steady_clock::time_point start;

public:
    void startTimer();
    double stopTimer();
};

#endif
