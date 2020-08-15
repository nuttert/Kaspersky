#pragma once
#include <string>

namespace reverser{
    class Writer{
        public:
        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual void WriteToken(const std::string& token) = 0;
    };
}