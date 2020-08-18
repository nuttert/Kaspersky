#include "Writer.hpp"
#include "Writer/Contract/WriterContract.hpp"
#include "Utilities/Exceptions/Exceptions.hpp"
#include <iostream>
#include <future>

namespace reverser
{
    void WriterImpl::Start() const
    {
        isRun = true;
    }
    void WriterImpl::Stop() const
    {
        isRun = false;
    }

    void WriterImpl::WriteToken(const Token &token) const
    {
        if (!isRun ||
            !WriterContract(token))
            return;
        static const auto STDOUT = 1;
        static timeval kTimeout = {1, 0};
        int descriptorIsActive;
        int letterIndex = 0;
        const auto &buffer = token.GetBuffer();

        fd_set descriptors;
        FD_SET(STDOUT, &descriptors);

        while (isRun &&
               letterIndex < buffer.size())
        {
            descriptorIsActive = select(2, NULL, &descriptors, NULL, &kTimeout);
            if (!descriptorIsActive)
                break;
            std::cout << buffer[letterIndex++];
        }
        if (descriptorIsActive < 0)
            throw exceptions::DescriptorException("Output file descriptor error!");
    }

    WriterImpl::~WriterImpl()
    {
        Stop();
    }
}; // namespace reverser