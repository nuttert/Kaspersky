#include <iostream>
#include <vector>
#include "TokenProcessor/impl/TokenProcessor.hpp"



int main(void){
    auto processor = std::make_shared<reverser::TokenProcessorImpl>();
    processor->Start();
    return 0;
}