#pragma once
#include <memory>

namespace reverser{

    class Interrupter;
    class TokenProcessor;

    class Runner {
    public:
        Runner(std::shared_ptr<TokenProcessor>, 
               std::shared_ptr<Interrupter>);
        virtual void Run() const = 0;
    protected:
        std::shared_ptr<TokenProcessor> processor;
        std::shared_ptr<Interrupter> interrupter;
    };
}