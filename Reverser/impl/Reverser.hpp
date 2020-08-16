#pragma once
#include <string>
#include "Reverser/Reverser.hpp"
#include "Models/Token.hpp"

namespace reverser{
    class ReverserImpl: public Reverser{
    public:
        Token ReverseWord(const Token& token) override;
    };
}