#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>
// implement a steady clock that begins at system time

class Clock {
public:
    Clock()
        : syncPoint_(std::chrono::system_clock::now())
        , steadyRef_(std::chrono::steady_clock::now())
    {
    }

    auto steady_now() -> std::chrono::system_clock::time_point
    {
        const auto elapsed = std::chrono::steady_clock::now() - steadyRef_;

        return syncPoint_ + std::chrono::duration_cast<std::chrono::system_clock::duration>(elapsed);
    }

    auto steady_now_ms() -> std::chrono::milliseconds
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(steady_now().time_since_epoch());
    }

private:
    const std::chrono::system_clock::time_point syncPoint_;
    const std::chrono::steady_clock::time_point steadyRef_;
};

#endif // CLOCK_HPP
