#include "Runner/impl/Runner.hpp"
#include "Interrupter/impl/Interrupter.hpp"
#include "TokenProcessor/impl/TokenProcessor.hpp"
#include "Reader/impl/Reader.hpp"
#include "Reverser/impl/Reverser.hpp"
#include "Writer/impl/Writer.hpp"


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <csignal>

namespace tests
{
    struct Tester;
    //#Mocks
    class RunnerImplMock: public reverser::RunnerImpl{
        public:
            using reverser::RunnerImpl::RunnerImpl;
        friend Tester;
    };
    // class InterrupterMock: public reverser::Interrupter{
    //     public:
    //         using reverser::Interrupter::Interrupter;
    //         MOCK_METHOD0(Start, void());
    //         MOCK_METHOD0(Stop, void());
    // };
    class RederMock: public reverser::Reader{
        public:
            using reverser::Reader::Reader;
            MOCK_METHOD0(Start, void());
            MOCK_METHOD0(Stop, void());
            MOCK_METHOD0(ReadToken, reverser::Token());
    };
    class WriterMock: public reverser::Writer{
        public:
            using reverser::Writer::Writer;
            MOCK_METHOD0(Start, void());
            MOCK_METHOD0(Stop, void());
            MOCK_METHOD1(WriteToken, void(const reverser::Token&));
    };
    class ReverserMock: public reverser::Reverser{
        public:
            using reverser::Reverser::Reverser;
            MOCK_METHOD1(ReverseWord, reverser::Token(const reverser::Token &token));
    };

    class Tester : public ::testing::Test
    {
    using Delegator = std::function<void()>;

    public:
        Tester() : delegator([]{}), ::testing::Test()
        {
            auto interrupter = std::make_shared<reverser::InterrupterImpl>(delegator);
            auto token_processor = std::make_shared<reverser::TokenProcessorImpl>();

            runner = std::make_shared<RunnerImplMock>(token_processor, interrupter);
        }
        void SetDelegator(const Delegator& delegator){
            this->delegator = delegator;
        }
        std::shared_ptr<RunnerImplMock> GetRunner(){
            return runner;
        }
        std::function<void(RunnerImplMock*)> GetNativeDelegator(){
            return &RunnerImplMock::SignalDelegator;
        }
    protected:
        Delegator delegator;
        std::shared_ptr<RunnerImplMock> runner;
    };
  

    //#Tests
    TEST_F(Tester, testReader)
    {
        bool delegator_active = false;

        auto native_delegator = GetNativeDelegator();
        auto runner = GetRunner();
        
        SetDelegator([runner,&native_delegator,&delegator_active]{
            delegator_active = true;
            native_delegator(runner.get());
        });
        auto result = std::async([runner]{runner->Run();});
        runner->Run();
        std::raise(SIGINT);
    }
} // namespace tests