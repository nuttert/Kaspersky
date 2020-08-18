#include "ReverserContract.hpp"

namespace reverser{
    bool ReverserContract(const Token& token){
        return token.GetType() == ETokenType::kLetters;
    }
}