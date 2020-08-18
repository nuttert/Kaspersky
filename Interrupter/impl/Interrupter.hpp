#pragma once
#include "Interrupter/Interrupter.hpp"

#include <atomic>
#include <functional>

namespace reverser
{
    class InterrupterImpl : public Interrupter
    {
    public:
        using Delegator = std::function<void()>;

    public:
        InterrupterImpl(const Delegator &delegator);
        void Start() const override;
        void Stop() const override;
        ~InterrupterImpl();

    private:
        void SignalHandlerImpl(int);

    private:
        mutable std::atomic<bool> isRun;
        Delegator delegator;
    };
} // namespace reverser