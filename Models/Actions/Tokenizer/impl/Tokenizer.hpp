#pragma once
#include <string>
#include "Models/Token.hpp"
#include "Models/Actions/Tokenizer/Tokenizer.hpp"

namespace reverser
{
    class ReverserImpl;

    class TokenizerImpl: public Tokenizer
    {
    friend ReverserImpl;
    public:
        TokenizerImpl()=default;

        bool AddToBuffer(int symbol, Token& token) const;
        void SetBuffer(const std::string &buffer, Token& token) const;

    private:
        bool NoneHandler(int symbol, Token& rhs) const;
        bool SymbolHandler(int symbol, Token& rhs) const;
        bool LetterHandler(int symbol, Token& rhs) const;
        bool EOFHandler(int symbol, Token& rhs) const;

    };
} // namespace reverser