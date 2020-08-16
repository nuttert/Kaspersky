#include "Token.hpp"
#include "Utilities/Utilities.hpp"
#include <stdexcept>

namespace reverser{
        bool Token::AddToBuffer(char symbol){
            switch(type){
                case ETokenType::kNone: return NoneHandler(symbol);
                case ETokenType::kSymbol: return SymbolHandler(symbol);
                case ETokenType::kLetter: return LetterHandler(symbol);
                case ETokenType::kEOF: return EOFHandler(symbol);
            }
            throw std::runtime_error("Undefined token type!");
        }

        bool Token::NoneHandler(char symbol){
            if(symbol == EOF){ type = ETokenType::kEOF; return false;}
            else if(utilities::isLetter(symbol)) type = ETokenType::kLetter;
            else type = ETokenType::kSymbol;
            buffer += symbol;
            return true;
        }
        bool Token::SymbolHandler(char symbol){
            if(symbol != EOF && ! utilities::isLetter(symbol)) {
                type = ETokenType::kSymbol;
                buffer += symbol;
            }else return false;
            return true;
        }
        bool Token::LetterHandler(char symbol){
            if(utilities::isLetter(symbol)) {
                type = ETokenType::kLetter;
                buffer += symbol;
            }else return false;
            return true;
        }
        bool Token::EOFHandler(char symbol){
            if(symbol == EOF){
                 type = ETokenType::kEOF;
                 return false;
            }else throw std::runtime_error("Token has EOF type, you can't add symbols to it!");
        }




        const std::string& Token::GetBuffer() const{
            return buffer;
        }
        std::string& Token::GetBuffer(){
            return buffer;
        }

        ETokenType Token::GetType() const{
            return type;
        }
}