#pragma once
#include <string>
#include <atomic>
#include "Models/Token.hpp"
#include "Reader/Reader.hpp"

namespace reverser{
    class ReaderImpl: public Reader{
        public:
            ReaderImpl();
            void Start() override;
            void Stop() override;
            Token ReadToken() const override;
            ~ReaderImpl();
        private:
            std::atomic<bool> isRun;
    };
}