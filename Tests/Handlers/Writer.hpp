#include "Tests/Tester.hpp"

#include <gtest/gtest.h>

using namespace tests;

TEST_F(Tester, test_writer)
{
    auto writer = std::make_shared<reverser::WriterImpl>();
    auto token_processor = std::make_shared<reverser::TokenProcessorImpl>(
        reader_mock,
        writer,
        reverser_mock
    );
    auto runner = std::make_shared<reverser::RunnerImpl>(
        token_processor,
        interrupter_mock
    );

    EXPECT_CALL(*interrupter_mock, Start()).
    Times(1);
    EXPECT_CALL(*interrupter_mock, Stop()).
    Times(1);
    EXPECT_CALL(*reader_mock, Start()).
    Times(1);
    EXPECT_CALL(*reader_mock, Stop()).
    Times(1);
    
    testing::Sequence s_reader, s_reverser;

    EXPECT_CALL(*reader_mock, ReadToken()).
    Times(::testing::AnyNumber()).
    WillRepeatedly(::testing::Return(reverser::Token()));

    EXPECT_CALL(*reverser_mock, ReverseWord(::testing::_)).
    Times(::testing::AnyNumber()).
    WillRepeatedly(::testing::Return(reverser::Token()));
    
    SequenceCallOutReader(s_reader,
    "Hello",
    "World",
    "!\n",
    "Today",
    "! 01.01.2000.\n",
    EOF);

    SequenceCallOutReverser(s_reverser,
    "Hello",
    "World",
    "!\n",
    "Today",
    "! 01.01.2000.\n",
    EOF);

    std::stringstream buffer;
    auto old = std::cout.rdbuf(buffer.rdbuf());

    auto result = std::async([runner]{runner->Run();});
    result.get();  
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(),"HelloWorld!\nToday! 01.01.2000.\n");

}