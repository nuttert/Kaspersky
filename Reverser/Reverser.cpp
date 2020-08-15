#include "Reverser.hpp"
#include <regex>


namespace reverser{
    std::string Reverser::ReverseWord(const Token& token){
        
        if(token.type == ETokenType::kWord){
            std::string tmp = token.buffer;
            std::reverse(tmp.begin(),tmp.end());
            return tmp;
        }  
        else return token.buffer;
    }
}