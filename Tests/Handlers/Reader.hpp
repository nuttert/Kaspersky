#include "Tests/Tester.hpp"

#include <gtest/gtest.h>

using namespace tests;

TEST_F(Tester, test_reader)
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
    EXPECT_CALL(*interrupter_mock, Stop()).
    Times(1);
    EXPECT_CALL(*writer_mock, Start()).
    Times(1);
    EXPECT_CALL(*writer_mock, Stop()).
    Times(1);
    
    testing::Sequence s_reverser;

    EXPECT_CALL(*reverser_mock, ReverseWord(testing::_)).
    Times(::testing::AnyNumber()).
    WillRepeatedly(::testing::Return(reverser::Token()));

    SequenceCallInReverser(s_reverser,
    "Hello",
    "World",
    "!\n",
    "Today",
    "! 01.01.2000.\n");

    EXPECT_CALL(*writer_mock, WriteToken(reverser::Token())).
    Times(::testing::AnyNumber());
    
    
    int PREV_FD = STDIN_FILENO;
    for (const auto & test_file_entry : fs::directory_iterator(kPathToData)){
        fs::path test_file_path = test_file_entry.path();
        auto test_fd = open(test_file_path.c_str(),O_RDONLY);
        dup2(test_fd,PREV_FD);
        PREV_FD = test_fd;
        runner->Run();
    }
    dup2(PREV_FD, STDIN_FILENO);
}
