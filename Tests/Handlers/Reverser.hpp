#include "Tests/Tester.hpp"

#include <gtest/gtest.h>

using namespace tests;

TEST_F(Tester, test_reverser)
{
    auto reverser = std::make_shared<reverser::ReverserImpl>();
    auto token_processor = std::make_shared<reverser::TokenProcessorImpl>(
        reader_mock,
        writer_mock,
        reverser
    );
    auto runner = std::make_shared<reverser::RunnerImpl>(
        token_processor,
        interrupter_mock
    );

    EXPECT_CALL(*interrupter_mock, Start()).
    Times(1);
    EXPECT_CALL(*interrupter_mock, Stop()).
    Times(1);
    EXPECT_CALL(*interrupter_mock, Wait()).
    Times(1);
    EXPECT_CALL(*writer_mock, Start()).
    Times(1);
    EXPECT_CALL(*writer_mock, Stop()).
    Times(1);
    EXPECT_CALL(*reader_mock, Start()).
    Times(1);
    EXPECT_CALL(*reader_mock, Stop()).
    Times(1);
    
    testing::Sequence s_reader, s_writer;

    EXPECT_CALL(*reader_mock, ReadToken()).
    Times(::testing::AnyNumber()).
    WillRepeatedly(::testing::Return(reverser::Token()));

    SequenceCallOutReader(s_reader,
    "Hello",
    "World",
    "!\n",
    "Today",
    "! 01.01.2000.\n",
    EOF);

    EXPECT_CALL(*writer_mock, WriteToken(reverser::Token())).
    Times(::testing::AnyNumber());

    SequenceCallInWriter(s_writer,
    "olleH",
    "dlroW",
    "!\n",
    "yadoT",
    "! 01.01.2000.\n"
    );
    

    auto result = std::async([runner]{runner->Run();});
}