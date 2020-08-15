#pragma once
#include <string>
#include "Models/Token.hpp"

namespace reverser{
    class Reverser{
        public:
        std::string ReverseWord(const Token& token);
    };
}