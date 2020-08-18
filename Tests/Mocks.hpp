#pragma once
#include "Runner/impl/Runner.hpp"
#include "Interrupter/impl/Interrupter.hpp"
#include "TokenProcessor/impl/TokenProcessor.hpp"
#include "Reader/impl/Reader.hpp"
#include "Reverser/impl/Reverser.hpp"
#include "Writer/impl/Writer.hpp"
#include "Models/Token.hpp"

#include <gmock/gmock.h>

namespace tests
{
    struct Tester;
    //#Mocks
    class ReaderMock: public reverser::Reader{
        public:
            using reverser::Reader::Reader;
            MOCK_CONST_METHOD0(Start, void());
            MOCK_CONST_METHOD0(Stop, void());
            MOCK_CONST_METHOD0(ReadToken, reverser::Token());
    };
    class WriterMock: public reverser::Writer{
        public:
            using reverser::Writer::Writer;
            MOCK_CONST_METHOD0(Start, void());
            MOCK_CONST_METHOD0(Stop, void());
            MOCK_CONST_METHOD1(WriteToken, void(const reverser::Token&));
    };
    class ReverserMock: public reverser::Reverser{
        public:
            using reverser::Reverser::Reverser;
            MOCK_CONST_METHOD1(ReverseWord, reverser::Token(const reverser::Token &token));
    };

        class TokenProcessorMock: public reverser::TokenProcessor{
        public:
            using reverser::TokenProcessor::TokenProcessor;
            MOCK_CONST_METHOD0(Start, void());
            MOCK_CONST_METHOD0(Stop, void());
            MOCK_CONST_METHOD0(Wait, void());
    };
    class InterrupterMock: public reverser::Interrupter{
        public:
            using reverser::Interrupter::Interrupter;
            MOCK_CONST_METHOD0(Start, void());
            MOCK_CONST_METHOD0(Stop, void());
    };
    class RunnerImplWrapper: public reverser::RunnerImpl{
        public:
            using reverser::RunnerImpl::RunnerImpl;
        friend Tester;
    };

}