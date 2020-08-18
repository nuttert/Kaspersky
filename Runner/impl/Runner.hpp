#pragma once
#include "Runner/Runner.hpp"
#include <atomic>

namespace reverser{

    class RunnerImpl: public Runner{
    public:
        using Runner::Runner;
        RunnerImpl();
        void Run() const override;
        operator bool() const override;
        void OnReady(OnReadyHandler&&) override;
    protected:
        void SignalDelegator();
    private:
        mutable std::atomic<bool> isRun;
        mutable std::atomic<bool> isReady;
        OnReadyHandler on_ready_handler;
    };
}