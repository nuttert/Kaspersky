#include "Runner.hpp"
#include "TokenProcessor/impl/TokenProcessor.hpp"
#include "Interrupter/impl/Interrupter.hpp"
#include <iostream>

namespace reverser{

        RunnerImpl::RunnerImpl():
        isRun(false),
        on_ready_handler([]{}),
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
                   isReady = true;
                   on_ready_handler();
                   processor->Wait();
                });
                result.wait();
                isRun = false;
        }
        RunnerImpl::operator bool() const{
                return isReady;
        }
        void RunnerImpl::OnReady(OnReadyHandler&& handler){
                on_ready_handler = std::move(handler);
        }
        void RunnerImpl::SignalDelegator(){
            processor->Stop();
            interrupter->Stop();
        }
}