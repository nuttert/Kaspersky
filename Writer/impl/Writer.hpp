#pragma once
#include <string>
#include "Writer/Writer.hpp"
#include <mutex>
#include <condition_variable>

namespace reverser
{
    class WriterImpl : public Writer
    {
    public:
        void Start() override;
        void Stop() override;
        void WriteToken(const Token &token) const;
        ~WriterImpl();

    private:
        std::atomic<bool> isRun;
    };
} // namespace reverser