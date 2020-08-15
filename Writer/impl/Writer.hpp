#pragma once
#include <string>
#include "Writer/Writer.hpp"

namespace reverser{
    class WriterImpl: public Writer{
    public:
        void Start();
        void Stop();
        void WriteToken(const std::string& token);
    };
}