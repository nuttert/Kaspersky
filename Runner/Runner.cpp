#include "Runner.hpp"
#include "Utilities/Exceptions/Exceptions.hpp"

namespace reverser{
    Runner::Runner(
            std::shared_ptr<TokenProcessor> processor,
            std::shared_ptr<Interrupter> interrupter):
                processor(processor),
                interrupter(interrupter){
                if( !processor ||
                    !interrupter) throw exceptions::InitializationException("You have to initialize token processor, interrupter!");
            };
}