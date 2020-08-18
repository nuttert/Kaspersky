#include "Runner/impl/Runner.hpp"

#include <iostream>


int main(void){
    try{
        auto runner = std::make_shared<reverser::RunnerImpl>();
        runner->Run();
    }catch(const std::exception& e){
        std::cerr << e.what();
    }
    return 0;
}