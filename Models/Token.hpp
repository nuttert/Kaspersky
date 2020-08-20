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
    class TokenizerImpl;

    class Token
    {
    public:
        Token()=default;

        const std::string &GetBuffer() const;
        ETokenType GetType() const;
        bool operator==(const Token& rhs) const;
    private:
        ETokenType type = ETokenType::kNone;
        std::string buffer{};

        friend ReverserImpl;
        friend TokenizerImpl;
    };
} // namespace reverser