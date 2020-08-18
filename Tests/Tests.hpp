#include "Runner/impl/Runner.hpp"
#include "Interrupter/impl/Interrupter.hpp"
#include "TokenProcessor/impl/TokenProcessor.hpp"
#include "Reader/impl/Reader.hpp"
#include "Reverser/impl/Reverser.hpp"
#include "Writer/impl/Writer.hpp"
#include "Models/Token.hpp"


#include <gtest/gtest.h>
#include <gmock/gmock.h>
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

        void SequenceCallReverser(const std::string& input, testing::Sequence& sequence){
            EXPECT_CALL(*reverser_mock, ReverseWord(reverser::Token(input))).
            InSequence(sequence).
            WillOnce(::testing::Return(reverser::Token()));
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
  

    //#Tests
    TEST_F(Tester, testInterrupter)
    {
        bool delegator_active = false;
        auto native_delegator = GetNativeDelegator();
        auto interrupter = std::make_shared<reverser::InterrupterImpl>(delegator);

        auto runner = std::make_shared<reverser::RunnerImpl>(
            token_processor_mock,
            interrupter
        );

        EXPECT_CALL(*token_processor_mock, Start()).
        Times(1);
        EXPECT_CALL(*token_processor_mock, Wait()).
        Times(1);
        
        SetDelegator([&native_delegator,
                      &delegator_active]{
            delegator_active = true;
        });
        runner->OnReady(
            [this]{cv.notify_one();}
        );
        runner->Run();
        {
            std::unique_lock<std::mutex> lk(mutex);
            cv.wait_for(lk, 3s, [runner]{return bool(*runner);});
        }
        std::raise(SIGINT);

        EXPECT_EQ(delegator_active, true);
    }

    TEST_F(Tester, testReader)
    {
        auto reader = std::make_shared<reverser::ReaderImpl>();
        auto token_processor = std::make_shared<reverser::TokenProcessorImpl>(
            reader,
            writer_mock,
            reverser_mock
        );
        auto runner = std::make_shared<reverser::RunnerImpl>(
            token_processor,
            interrupter_mock
        );

        EXPECT_CALL(*interrupter_mock, Start()).
        Times(1);
        EXPECT_CALL(*writer_mock, Start()).
        Times(1);
        EXPECT_CALL(*writer_mock, Stop()).
        Times(1);
        
        testing::Sequence s;

        EXPECT_CALL(*reverser_mock, ReverseWord(testing::_)).
        Times(::testing::AnyNumber()).
        WillRepeatedly(::testing::Return(reverser::Token()));

        SequenceCallReverser("Hello",s);
        SequenceCallReverser("World",s);
        SequenceCallReverser("!\n",s);
        SequenceCallReverser("Today",s);
        SequenceCallReverser("! 01.01.2000.\n",s);

        EXPECT_CALL(*writer_mock, WriteToken(reverser::Token())).
        Times(::testing::AnyNumber());
        
        runner->OnReady(
            [this]{cv.notify_one();}
        );
        for (const auto & test_file_entry : fs::directory_iterator(kPathToData)){
            fs::path test_file_path = test_file_entry.path();
            auto test_fd = open(test_file_path.c_str(),O_RDONLY);
            dup2(test_fd,STDIN_FILENO);
            auto result = std::async([runner]{runner->Run();});
            {
                std::unique_lock<std::mutex> lk(mutex);
                cv.wait_for(lk, 3s, [runner]{return bool(*runner);});
            }
        }


        // EXPECT_EQ(delegator_active, true);
    }
} // namespace tests