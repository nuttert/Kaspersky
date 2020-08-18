#pragma once
#include "Models/Token.hpp"
#include "Reader/Reader.hpp"

#include <string>
#include <atomic>

namespace reverser
{
    class ReaderImpl : public Reader
    {
    public:
        ReaderImpl();
        void Start() override;
        void Stop() override;
        Token ReadToken() const override;
        ~ReaderImpl();

    private:
        std::atomic<bool> isRun;
    };
} // namespace reverser