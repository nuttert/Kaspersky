#include "Token.hpp"
#include "Utilities/Functions/Functions.hpp"
#include "Utilities/Exceptions/Exceptions.hpp"

#include <stdexcept>

namespace reverser
{

    const std::string &Token::GetBuffer() const
    {
        return buffer;
    }
    
    ETokenType Token::GetType() const
    {
        return type;
    }
    bool Token::operator==(const Token& rhs) const{
        return buffer == rhs.buffer;
    }
} // namespace reverser