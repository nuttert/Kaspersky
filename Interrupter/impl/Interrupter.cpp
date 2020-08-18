#include "Interrupter.hpp"
#include "Utilities/Exceptions/Exceptions.hpp"

#include <csignal>
#include <functional>
#include <iostream>

namespace reverser
{

    namespace
    {
        std::function<void(int)> SignalHandlerImpl_;
        void SignalHandler(int signal)
        {
            if (SignalHandlerImpl_)
                SignalHandlerImpl_(signal);
            else
                SIG_DFL(signal);
        }
    } // namespace
    

    InterrupterImpl::InterrupterImpl(const Delegator &delegator) : delegator(delegator)
    {
        if (!delegator)
            throw exceptions::DelegatorException();
        SignalHandlerImpl_ = std::bind(&InterrupterImpl::SignalHandlerImpl,
                                       this,
                                       std::placeholders::_1);
    }

    void InterrupterImpl::Start() const
    {
        if (isRun)
            return;
        isRun = true;
        std::signal(SIGINT, SignalHandler);
    }
    void InterrupterImpl::Stop() const
    {
        if (!isRun)
            return;
        isRun = false;
        std::signal(SIGINT, SIG_DFL);
    }
    void InterrupterImpl::SignalHandlerImpl(int signal)
    {
        std::cout << std::endl
                  << "Interrupt" << std::endl;
        delegator();
    }
    InterrupterImpl::~InterrupterImpl()
    {
        Stop();
    }
} // namespace reverser