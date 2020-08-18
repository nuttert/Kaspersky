#pragma once
#include "Mocks.hpp"

#include <gtest/gtest.h>
#include <csignal>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include <filesystem>
#include <fcntl.h>

using namespace std::chrono_literals;
using ::testing::AtLeast;
namespace fs = std::filesystem;

namespace tests
{

namespace{
        const auto kPathToData = "../Tests/Data";
}

 class Tester : public ::testing::Test
    {
    using Delegator = std::function<void()>;
    public:
        Tester() : delegator([]{}), ::testing::Test()
        {
            interrupter_mock = std::make_shared<InterrupterMock>();
            reader_mock = std::make_shared<ReaderMock>();
            writer_mock = std::make_shared<WriterMock>();
            reverser_mock = std::make_shared<ReverserMock>();
            token_processor_mock = std::make_shared<TokenProcessorMock>(
                reader_mock,
                writer_mock,
                reverser_mock
            );
        }

        std::function<void(RunnerImplWrapper*)> GetNativeDelegator(){
            return &RunnerImplWrapper::SignalDelegator;
        }
        void SetDelegator(const Delegator& delegator){
            this->delegator = delegator;
        }
        
        template<typename ...Args>
        void SequenceCallInReverser(testing::Sequence& sequence, const Args& ...args){
            (EXPECT_CALL(*reverser_mock, ReverseWord(reverser::Token(args))).
            InSequence(sequence), ...);
        }
        template<typename ...Args>
        void SequenceCallOutReverser(testing::Sequence& sequence, const Args& ...args){
            (EXPECT_CALL(*reverser_mock, ReverseWord(::testing::_)).
            InSequence(sequence).
            WillOnce(::testing::Return(reverser::Token(args))), ...);
        }
        template<typename ...Args>
        void SequenceCallOutReader(testing::Sequence& sequence, const Args& ...args){
            (EXPECT_CALL(*reader_mock, ReadToken()).
            InSequence(sequence).
            WillOnce(::testing::Return(reverser::Token(args))), ...);
        }
        template<typename ...Args>
        void SequenceCallInWriter(testing::Sequence& sequence, const Args& ...args){
            (EXPECT_CALL(*writer_mock,WriteToken(reverser::Token(args))).
            InSequence(sequence), ...);
        }

    protected:
        Delegator delegator;
        std::shared_ptr<InterrupterMock> interrupter_mock;
        std::shared_ptr<ReaderMock> reader_mock;
        std::shared_ptr<WriterMock> writer_mock;
        std::shared_ptr<ReverserMock> reverser_mock;
        std::shared_ptr<TokenProcessorMock> token_processor_mock;

        std::mutex mutex;
        std::condition_variable cv;
    };
}