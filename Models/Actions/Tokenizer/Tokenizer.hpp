#pragma once
#include <string>
#include "Models/Token.hpp"

namespace reverser
{
    class ReverserImpl;

    class Tokenizer
    {
    friend ReverserImpl;
    public:
        virtual bool AddToBuffer(int symbol, Token& token) const = 0;
        virtual void SetBuffer(const std::string &buffer, Token& token) const = 0;
    };
} // namespace reverser