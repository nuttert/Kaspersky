#pragma once
#include <string>
#include "Models/Token.hpp"

namespace reverser
{
    class Reverser
    {
    public:
        virtual Token ReverseWord(const Token &token) const = 0;
    };
} // namespace reverser