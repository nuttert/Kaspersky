#include "Reverser.hpp"
#include "Reverser/Contract/ReverserContract.hpp"
#include <regex>


namespace reverser{
    Token ReverserImpl::ReverseWord(const Token& token) const{
        if(ReverserContract(token)){
            Token reversed_token = token;
            std::reverse(reversed_token.buffer.begin(),
                         reversed_token.buffer.end());
            return reversed_token;
        }  
        else return token;
    }
}