#include "TokenProcessor.hpp"

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
                    !reverser) throw std::runtime_error("You have to initialize reader, writer, reverser!");
            };
}