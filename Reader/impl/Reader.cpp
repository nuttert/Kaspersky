#include "Reader.hpp"
#include "Utilities/Exceptions/Exceptions.hpp"

#include <fstream>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <sys/select.h>

namespace reverser
{

    ReaderImpl::ReaderImpl() : isRun(false) {}

    void ReaderImpl::Start()
    {
        isRun = true;
    }
    void ReaderImpl::Stop()
    {
        isRun = false;
    }

    Token ReaderImpl::ReadToken() const
    {
        static const auto STDIN = 0;
        static timeval kTimeout = {0, 100};
        int new_symbol;
        int descriptorIsActive;

        Token token;
        fd_set descriptors;
        FD_ZERO(&descriptors);
        FD_SET(STDIN, &descriptors);

        while (isRun)
        {
            descriptorIsActive = select(1, &descriptors, NULL, NULL, &kTimeout);
            if (!descriptorIsActive)
                break;
            if (!token.AddToBuffer(new_symbol = getchar()))
                break;
        }
        if (descriptorIsActive < 0)
            throw exceptions::DescriptorException("Input file descriptor error!");
        if (descriptorIsActive)
            ungetc(new_symbol, stdin);
        return token;
    }
    ReaderImpl::~ReaderImpl()
    {
        Stop();
    }
} // namespace reverser