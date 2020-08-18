#pragma once
#include "TokenProcessor/TokenProcessor.hpp"
#include <mutex>
#include <future>
#include <atomic>

namespace reverser
{
    class TokenProcessorImpl : public TokenProcessor
    {
    public:
        using TokenProcessor::TokenProcessor;
        TokenProcessorImpl();
        void Start() const override;
        void Stop() const override;
        void Wait() const override;

        ~TokenProcessorImpl();

    private:
        void StopImpl() const;

    private:
        mutable std::atomic<bool> isRun;
        mutable std::future<void> runner;
    };
} // namespace reverser