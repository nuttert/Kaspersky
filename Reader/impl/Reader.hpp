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
        void Start() const override;
        void Stop() const override;
        Token ReadToken() const override;
        ~ReaderImpl();

    private:
        mutable std::atomic<bool> isRun;
    };
} // namespace reverser