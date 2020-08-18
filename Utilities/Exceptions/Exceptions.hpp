#pragma once
#include <string>

namespace reverser::exceptions
{
    struct ReverserException : public std::exception
    {
        using std::exception::exception;
    };

    class DelegatorException : public ReverserException
    {
    public:
        const char *what() const noexcept override
        {
            return "Invalid delegator!";
        }
    };

    class TokenException : public ReverserException
    {
    public:
        TokenException(const std::string &message) : message(message) {}
        const char *what() const noexcept override
        {
            return message.c_str();
        }

    private:
        std::string message;
    };

    class DescriptorException : public ReverserException
    {
    public:
        DescriptorException(const std::string &message) : message(message) {}
        const char *what() const noexcept override
        {
            return message.c_str();
        }

    private:
        std::string message;
    };

    class InitializationException : public ReverserException
    {
    public:
        InitializationException(const std::string &message) : message(message) {}
        const char *what() const noexcept override
        {
            return message.c_str();
        }

    private:
        std::string message;
    };
} // namespace reverser::exceptions