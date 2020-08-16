#include <future>
#include <iostream>

#include "TokenProcessor.hpp"
#include "TokenProcessor/Contract/TokenProcessorContract.hpp"
#include "Models/Token.hpp"

#include "Reverser/impl/Reverser.hpp"
#include "Writer/impl/Writer.hpp"
#include "Reader/impl/Reader.hpp"


namespace reverser{
        TokenProcessorImpl::TokenProcessorImpl():
        isRun(false),
        TokenProcessor(std::make_shared<ReaderImpl>(),
                       std::make_shared<WriterImpl>(),
                       std::make_shared<ReverserImpl>()){}

        void TokenProcessorImpl::Start(){
            isRun = true;
            reader->Start();
            writer->Start();

            runner = std::async([this](){
                while(isRun){
                    auto token = reader->ReadToken();
                    auto reversed_token = reverser->ReverseWord(token);
                    if(!TokenProcessorContract(token)) isRun = false;
                    writer->WriteToken(reversed_token);
                }
             }
            );
        }
        void TokenProcessorImpl::StopImpl(){
            //  isRun = false;
             writer->Stop();
             reader->Stop();
        }

        void TokenProcessorImpl::Stop(){
             StopImpl();
             runner.get();
        }

        TokenProcessorImpl::~TokenProcessorImpl(){
            Stop();
        }
}