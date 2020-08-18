#include "Tests.hpp"

#include <gtest/gtest.h>

using namespace tests;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}