#include "Tokenizer.hpp"
#include "Utilities/Functions/Functions.hpp"
#include "Utilities/Exceptions/Exceptions.hpp"

#include <stdexcept>

namespace reverser
{

    void TokenizerImpl::SetBuffer(const std::string &buffer, Token& token)const
    {
        for (const auto &symbol : buffer)
            if (!AddToBuffer(symbol, token))
                throw exceptions::TokenException("Different token types!");
    }

    bool TokenizerImpl::AddToBuffer(int symbol, Token& rhs) const
    {
        switch (rhs.type)
        {
            case ETokenType::kNone: return NoneHandler(symbol, rhs);
            case ETokenType::kSymbols: return SymbolHandler(symbol, rhs);
            case ETokenType::kLetters: return LetterHandler(symbol, rhs);
            case ETokenType::kEOF: return EOFHandler(symbol, rhs);
        }
        throw exceptions::TokenException("Undefined token type!");
    }

    bool TokenizerImpl::NoneHandler(int symbol, Token& rhs) const
    {
        if (symbol == EOF)
        {
            rhs.type = ETokenType::kEOF;
            return false;
        }
        else if (utilities::isLetter(symbol))
            rhs.type = ETokenType::kLetters;
        else
            rhs.type = ETokenType::kSymbols;
        rhs.buffer += symbol;
        return true;
    }

    bool TokenizerImpl::SymbolHandler(int symbol, Token& rhs)const
    {
        if (symbol != EOF && !utilities::isLetter(symbol))
        {
            rhs.type = ETokenType::kSymbols;
            rhs.buffer += symbol;
        }
        else
            return false;
        return true;
    }

    bool TokenizerImpl::LetterHandler(int symbol, Token& rhs)const
    {
        if (utilities::isLetter(symbol))
        {
            rhs.type = ETokenType::kLetters;
            rhs.buffer += symbol;
        }
        else
            return false;
        return true;
    }

    bool TokenizerImpl::EOFHandler(int symbol, Token& rhs)const
    {
        if (symbol == EOF)
        {
            rhs.type = ETokenType::kEOF;
            return false;
        }
        else
            throw exceptions::TokenException("Token has EOF type, you can't add symbols to it!");
    }

} // namespace reverser