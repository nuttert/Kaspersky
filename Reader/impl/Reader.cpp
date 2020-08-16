#include "Reader.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <sys/select.h>

namespace reverser{

    ReaderImpl::ReaderImpl():isRun(false){}

    void ReaderImpl::Start(){
        isRun = true;
    }
    void ReaderImpl::Stop(){
        isRun = false;
    }

    Token ReaderImpl::ReadToken() const{
       static const auto STDIN = 0;
       int new_symbol;
       int descriptorIsActive;

       Token token;
       fd_set descriptors;
       FD_SET(STDIN, &descriptors);

       while(isRun  &&
             (descriptorIsActive = select(1, &descriptors, NULL, NULL, NULL)) &&
             token.AddToBuffer(new_symbol = getchar()));
       if(descriptorIsActive < 0) throw std::runtime_error("File descriptor error!");

       ungetc(new_symbol, stdin);
       return token;
    }
    ReaderImpl::~ReaderImpl(){
        Stop();
    }
}