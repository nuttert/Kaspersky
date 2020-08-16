#include "Writer.hpp"
#include <iostream>
#include <future>

namespace reverser{
        void WriterImpl::Start(){
            isRun = true;
        }
        void WriterImpl::Stop(){
            isRun = false;
            cv.notify_one();
        }

        void WriterImpl::WriteToken(const Token& token) const{
            if(!isRun) return;
            std::atomic<bool> stopSession = false;
            auto runner = std::async([&stopSession,&token]{
                std::cout << token.GetBuffer();
                stopSession = true;
            });
            {
                std::unique_lock<std::mutex> lock(mutex);
                cv.wait(lock,[this,&stopSession]{return stopSession || !isRun;});
            }
        }

        WriterImpl::~WriterImpl(){
            Stop();
        }
};