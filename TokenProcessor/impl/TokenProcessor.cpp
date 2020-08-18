#include <future>
#include <iostream>

#include "TokenProcessor.hpp"
#include "TokenProcessor/Contract/TokenProcessorContract.hpp"
#include "Models/Token.hpp"

#include "Reverser/impl/Reverser.hpp"
#include "Writer/impl/Writer.hpp"
#include "Reader/impl/Reader.hpp"

namespace reverser
{
    TokenProcessorImpl::TokenProcessorImpl() : isRun(false),
                                               TokenProcessor(std::make_shared<ReaderImpl>(),
                                                              std::make_shared<WriterImpl>(),
                                                              std::make_shared<ReverserImpl>()) {}

    void TokenProcessorImpl::Start() const
    {
        isRun = true;
        reader->Start();
        writer->Start();
        runner = std::async([this]() {
            while (isRun)
            {
                auto token = reader->ReadToken();
                if (!TokenProcessorContract(token))
                    StopImpl();
                auto reversed_token = reverser->ReverseWord(token);
                writer->WriteToken(reversed_token);
            }
        });
    }
    void TokenProcessorImpl::Wait() const
    {
        runner.wait();
    }
    void TokenProcessorImpl::StopImpl() const
    {
        isRun = false;
        writer->Stop();
        reader->Stop();
    }

    void TokenProcessorImpl::Stop() const
    {
        if(!isRun) return;
        StopImpl();
        runner.wait();
    }

    TokenProcessorImpl::~TokenProcessorImpl()
    {
        Stop();
    }
} // namespace reverser