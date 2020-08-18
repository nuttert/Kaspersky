#include "TokenProcessorContract.hpp"

namespace reverser{
    bool TokenProcessorContract(const Token& token){
        return token.GetType() != ETokenType::kEOF;
    }
}