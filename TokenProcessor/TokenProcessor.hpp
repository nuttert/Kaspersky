#pragma once
#include <memory>

namespace reverser{

    class Reader;
    class Writer;
    class Reverser;

    class TokenProcessor{
    public:
        TokenProcessor(
            std::shared_ptr<Reader>,
            std::shared_ptr<Writer>,
            std::shared_ptr<Reverser>);
        virtual void Start() const  = 0;
        virtual void Stop() const = 0;
        virtual void Wait() const = 0;
    protected:
        std::shared_ptr<Reader> reader;
        std::shared_ptr<Writer> writer;
        std::shared_ptr<Reverser> reverser;
    };
}