#pragma once
#include <string>
#include "Models/Token.hpp"

namespace reverser{
    class Reader{
        public:
            virtual void Start() = 0;
            virtual void Stop() = 0;
            virtual Token ReadToken() = 0;
    };
}