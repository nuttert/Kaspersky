#include "Tests/Tester.hpp"

#include <gtest/gtest.h>
using namespace tests;

TEST_F(Tester, test_interrupter)
{
    bool delegator_active = false;
    auto delegator = [
                    this,
                    &delegator_active]{
                    delegator_active = true;
                    cv.notify_one();
    };
    auto interrupter = std::make_shared<reverser::InterrupterImpl>(delegator);

    auto runner = std::make_shared<reverser::RunnerImpl>(
        token_processor_mock,
        interrupter
    );

    EXPECT_CALL(*token_processor_mock, Start()).
    Times(1);
    EXPECT_CALL(*token_processor_mock, Wait()).
    Times(1);
    

    auto result = std::async([runner]{runner->Run();});
    std::this_thread::sleep_for(0.4s);
    
    std::raise(SIGINT);
    {
         std::unique_lock<std::mutex> lk(mutex);
         cv.wait_for(lk ,0.5s, [delegator_active]{return delegator_active;});
    }

    EXPECT_EQ(delegator_active, true);
}
