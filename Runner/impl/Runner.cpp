#include "Runner.hpp"
#include "TokenProcessor/impl/TokenProcessor.hpp"
#include "Interrupter/impl/Interrupter.hpp"
#include <iostream>

namespace reverser{

        RunnerImpl::RunnerImpl():
        isRun(false),
        Runner(std::make_shared<TokenProcessorImpl>(),
               std::make_shared<InterrupterImpl>(
                            std::bind(&RunnerImpl::SignalDelegator,this)))
                {}

        void RunnerImpl::Run() const{
               if(isRun) std::runtime_error("Runner already started!");
               isRun = true;
               auto result = std::async([this]{
                   interrupter->Start();
                   processor->Start();
                   processor->Wait();
                });
        }
        void RunnerImpl::SignalDelegator(){
            processor->Stop();
            interrupter->Stop();
        }
}