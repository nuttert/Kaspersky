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
        void Start() const  override;
        void Stop() const override;
        void WriteToken(const Token &token) const;
        ~WriterImpl();

    private:
        mutable std::atomic<bool> isRun;
    };
} // namespace reverser