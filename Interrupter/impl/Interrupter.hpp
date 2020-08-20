#pragma once
#include "Interrupter/Interrupter.hpp"

#include <atomic>
#include <future>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <functional>

namespace reverser
{
    class InterrupterImpl : public Interrupter
    {
    public:
        using Delegator = std::function<void()>;
        using InterrupterRunner = std::future<void>;
    public:
        InterrupterImpl(const Delegator &delegator);
        void Start() const override;
        void Stop() const override;
        void Wait()const override;
        ~InterrupterImpl();

    private:
        void SignalHandlerImpl(int);

    private:
        mutable std::atomic<bool> isRun;
        mutable std::atomic<bool> signal;
        mutable std::mutex mutex;
        mutable std::condition_variable cv;
        mutable std::vector<InterrupterRunner> runners;

        Delegator delegator;
    };
} // namespace reverser