#include "Writer.hpp"
#include <iostream>

namespace reverser{
        void WriterImpl::Start(){

        }
        void WriterImpl::Stop(){

        }
        void WriterImpl::WriteToken(const std::string& token){
            std::cout << token;
        }
};