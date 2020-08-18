#pragma once
#include "Models/Token.hpp"

#include <string>

namespace reverser
{
    class Reader
    {
    public:
        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual Token ReadToken() const = 0;
    };
} // namespace reverser