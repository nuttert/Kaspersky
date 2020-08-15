#include "Reader.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <stdio.h>


namespace reverser{

    void ReaderImpl::Start(){

    }
    void ReaderImpl::Stop(){
        
    }

    Token ReaderImpl::ReadToken(){
       static std::regex regex("[a-zA-Zа-яА-Я]"); 
       char new_symbol = getchar();
       char temp = static_cast<char>(new_symbol);
       auto str_symbol = std::string(1,temp);

       Token token;
     
        if(std::regex_match(str_symbol, regex))
            token.type = ETokenType::kWord;
        else token.type = ETokenType::kSymbol;
    
       while(new_symbol != EOF){
           temp = static_cast<char>(new_symbol);
           str_symbol = std::string(1,temp);

           bool currentIsAlpha = std::regex_match(str_symbol, regex);

           if(currentIsAlpha == (token.type == ETokenType::kWord))
               token.buffer += new_symbol;
            else{
                ungetc(new_symbol, stdin);
                break;
            }
           new_symbol = getchar();
       }
       if(new_symbol == EOF)
            token.type = ETokenType::kEOF;
        return token;
    }
}