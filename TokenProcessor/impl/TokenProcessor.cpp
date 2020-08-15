#include <future>
#include <iostream>

#include "TokenProcessor.hpp"
#include "Models/Token.hpp"
#include "Reverser/Reverser.hpp"
#include "Writer/impl/Writer.hpp"
#include "Reader/impl/Reader.hpp"


namespace reverser{
        TokenProcessorImpl::TokenProcessorImpl():
        isRun(false),
        TokenProcessor(std::make_shared<ReaderImpl>(),
                       std::make_shared<WriterImpl>(),
                       std::make_shared<Reverser>()){}

        void TokenProcessorImpl::Start(){
            isRun = true;
            runner = std::async([this](){
                while(isRun){
                    auto token = reader->ReadToken();
                    auto reversed_token = reverser->ReverseWord(token);
                    if(token.type == ETokenType::kEOF)
                        isRun = false;
                    writer->WriteToken(reversed_token);
                }
             }
            );
        }

        void TokenProcessorImpl::Stop(){
             isRun = false;
             runner.get();
        }
}