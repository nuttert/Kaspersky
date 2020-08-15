#pragma once
#include "TokenProcessor/TokenProcessor.hpp"
#include <mutex>
#include <future>
#include <atomic>

namespace reverser{
    class TokenProcessorImpl: public TokenProcessor{
    public:
        TokenProcessorImpl();
        void Start() override;
        void Stop() override;
    private:
        std::atomic<bool> isRun;
        std::mutex mutex;
        std::future<void> runner;
    };
}