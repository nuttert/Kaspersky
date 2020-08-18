#include "TokenProcessor.hpp"
#include "Utilities/Exceptions/Exceptions.hpp"

namespace reverser{
    TokenProcessor::TokenProcessor(
            std::shared_ptr<Reader> reader,
            std::shared_ptr<Writer> writer,
            std::shared_ptr<Reverser> reverser):
            reader(reader),
            writer(writer),
            reverser(reverser){
                if( !reader ||
                    !writer ||
                    !reverser) throw exceptions::InitializationException("You have to initialize reader, writer, reverser!");
            };
}