#pragma once
#include "Models/Token.hpp"

#include <string>

namespace reverser
{
    class Reader
    {
    public:
        virtual void Start() const = 0;
        virtual void Stop() const = 0;
        virtual Token ReadToken() const = 0;
    };
} // namespace reverser