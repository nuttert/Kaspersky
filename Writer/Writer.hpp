#pragma once
#include <string>
#include "Models/Token.hpp"

namespace reverser{
    class Writer{
        public:
        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual void WriteToken(const Token& token) const = 0;
    };
}