#include "Reader.hpp"
#include "Utilities/Exceptions/Exceptions.hpp"

namespace reverser{
    Reader::Reader(
            std::shared_ptr<Tokenizer> tokenizer):
                tokenizer(tokenizer){
                if( !tokenizer)
                     throw exceptions::InitializationException("You have to initialize tokenizer!");
            };
}