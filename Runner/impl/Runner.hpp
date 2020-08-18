#pragma once
#include "Runner/Runner.hpp"
#include <atomic>

namespace reverser{

    class RunnerImpl: public Runner{
    public:
        using Runner::Runner;
        RunnerImpl();
        void Run() const override;
    protected:
        void SignalDelegator();
    private:
        mutable std::atomic<bool> isRun;
    };
}