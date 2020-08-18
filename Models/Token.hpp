#pragma once
#include <string>

namespace reverser
{
    enum class ETokenType
    {
        kLetters,
        kSymbols,
        kEOF,
        kNone
    };

    class ReverserImpl;

    class Token
    {
    public:
        Token(const std::string& buffer);
        Token(const char symbol);
        Token()=default;

        bool AddToBuffer(int symbol);
        void SetBuffer(const std::string &buffer);

        const std::string &GetBuffer() const;
        std::string &GetBuffer();
        
        ETokenType GetType() const;
        bool operator==(const Token& rhs) const;

    private:
        bool NoneHandler(int symbol);
        bool SymbolHandler(int symbol);
        bool LetterHandler(int symbol);
        bool EOFHandler(int symbol);

    private:
        ETokenType type = ETokenType::kNone;
        std::string buffer{};

        friend ReverserImpl;
    };
} // namespace reverser