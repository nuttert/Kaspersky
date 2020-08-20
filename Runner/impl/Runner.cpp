#include "Runner.hpp"
#include "TokenProcessor/impl/TokenProcessor.hpp"
#include "Interrupter/impl/Interrupter.hpp"
#include <iostream>
using namespace std::chrono_literals;
namespace reverser
{

        RunnerImpl::RunnerImpl() : isRun(false),
                                   Runner(std::make_shared<TokenProcessorImpl>(),
                                          std::make_shared<InterrupterImpl>(
                                              std::bind(&RunnerImpl::SignalDelegator, this)))
        {
        }

        void RunnerImpl::Run() const
        {
                if (isRun)
                        std::runtime_error("Runner already started!");
                isRun = true;
               
                interrupter->Start();
                processor->Start();

                processor->Wait();
                interrupter->Wait();

                isRun = false;
                processor->Stop();
                interrupter->Stop();
        }

        void RunnerImpl::SignalDelegator()
        {
                processor->Stop();
                interrupter->Stop();
        }
} // namespace reverser