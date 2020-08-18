#include "WriterContract.hpp"

namespace reverser
{
    bool WriterContract(const Token &token)
    {
        return token.GetType() != ETokenType::kNone;
    }
} // namespace reverser