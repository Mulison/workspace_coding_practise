#include <atomic>
#include <thread>
#include <iostream>
#include <functional>


class MultiThreadState
{
public:
    MultiThreadState();
    std::atomic<int> sharedState;
    void thread_2();
    void thread_3();


// private:

};