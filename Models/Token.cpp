#include "Token.hpp"
#include "Utilities/Functions/Functions.hpp"
#include "Utilities/Exceptions/Exceptions.hpp"

#include <stdexcept>

namespace reverser
{
    void Token::SetBuffer(const std::string &buffer)
    {
        for (const auto &symbol : buffer)
            if (!AddToBuffer(symbol))
                throw exceptions::TokenException("Different token types!");
    }

    bool Token::AddToBuffer(char symbol)
    {
        switch (type)
        {
        case ETokenType::kNone: return NoneHandler(symbol);
        case ETokenType::kSymbol: return SymbolHandler(symbol);
        case ETokenType::kLetter: return LetterHandler(symbol);
        case ETokenType::kEOF: return EOFHandler(symbol);
        }
        throw exceptions::TokenException("Undefined token type!");
    }

    bool Token::NoneHandler(char symbol)
    {
        if (symbol == EOF)
        {
            type = ETokenType::kEOF;
            return false;
        }
        else if (utilities::isLetter(symbol))
            type = ETokenType::kLetter;
        else
            type = ETokenType::kSymbol;
        buffer += symbol;
        return true;
    }

    bool Token::SymbolHandler(char symbol)
    {
        if (symbol != EOF && !utilities::isLetter(symbol))
        {
            type = ETokenType::kSymbol;
            buffer += symbol;
        }
        else
            return false;
        return true;
    }

    bool Token::LetterHandler(char symbol)
    {
        if (utilities::isLetter(symbol))
        {
            type = ETokenType::kLetter;
            buffer += symbol;
        }
        else
            return false;
        return true;
    }

    bool Token::EOFHandler(char symbol)
    {
        if (symbol == EOF)
        {
            type = ETokenType::kEOF;
            return false;
        }
        else
            throw exceptions::TokenException("Token has EOF type, you can't add symbols to it!");
    }

    const std::string &Token::GetBuffer() const
    {
        return buffer;
    }
    std::string &Token::GetBuffer()
    {
        return buffer;
    }

    ETokenType Token::GetType() const
    {
        return type;
    }
} // namespace reverser