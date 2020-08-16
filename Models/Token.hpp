#pragma once
#include <string>


namespace reverser{
    enum class ETokenType{
        kLetter,
        kSymbol,
        kEOF,
        kNone
    };

    class ReverserImpl;

    class Token{
    public:
        bool AddToBuffer(char symbol);

        const std::string& GetBuffer() const;
              std::string& GetBuffer();
        ETokenType GetType() const;
    private:
        bool NoneHandler(char symbol);
        bool SymbolHandler(char symbol);
        bool LetterHandler(char symbol);
        bool EOFHandler(char symbol);
    private:
        ETokenType type = ETokenType::kNone;
        std::string buffer;

        friend ReverserImpl;
    };
}