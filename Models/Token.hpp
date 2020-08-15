#pragma once
#include <string>


namespace reverser{
    enum class ETokenType{
        kWord,
        kSymbol,
        kEOF
    };

    struct Token{
        ETokenType type;
        std::string buffer;
    };
}