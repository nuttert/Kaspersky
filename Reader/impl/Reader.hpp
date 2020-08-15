#pragma once
#include <string>
#include "Models/Token.hpp"
#include "Reader/Reader.hpp"

namespace reverser{
    class ReaderImpl: public Reader{
        public:
            void Start() override;
            void Stop() override;
            Token ReadToken() override;
    };
}