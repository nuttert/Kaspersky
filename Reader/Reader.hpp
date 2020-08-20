#pragma once
#include "Models/Token.hpp"

#include <string>
#include <memory>

namespace reverser
{
    class Tokenizer;
    class Reader
    {
    public:
        Reader(std::shared_ptr<Tokenizer>);
        virtual void Start() const = 0;
        virtual void Stop() const = 0;
        virtual Token ReadToken() const = 0;
    protected:
        std::shared_ptr<Tokenizer> tokenizer;
    };
} // namespace reverser