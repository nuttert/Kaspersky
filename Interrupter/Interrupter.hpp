#pragma once

namespace reverser
{
    class Interrupter
    {
    public:
        virtual void Start() const = 0;
        virtual void Stop() const = 0;
        ~Interrupter() = default;
    };
} // namespace reverser