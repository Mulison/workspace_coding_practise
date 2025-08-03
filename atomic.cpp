#include "atomic.hpp"

MultiThreadState::MultiThreadState() : sharedState(0)
{}


void MultiThreadState::thread_2()
{
    sharedState.store(2);
}

void MultiThreadState::thread_3()
{
    sharedState.store(3);
}

int main(int argc, char **argv)
{
    MultiThreadState multi_thread_state;
    multi_thread_state.sharedState.store(1);
    // std::thread{std::bind(MultiThreadState::thread_2, &multi_thread_state)}.detach();
    // std::cout << multi_thread_state.sharedState.load() << std::endl ;
    // std::thread{std::bind(MultiThreadState::thread_3, &multi_thread_state)}.detach();
    // std::cout << multi_thread_state.sharedState.load() << std::endl;

    std::thread t2(&MultiThreadState::thread_2, &multi_thread_state);
    t2.join(); // Wait for thread_2 to complete
    std::cout << "After thread_2: " << multi_thread_state.sharedState.load() << std::endl;

    std::thread t3(&MultiThreadState::thread_3, &multi_thread_state);
    t3.join(); // Wait for thread_3 to complete
    std::cout << "After thread_3: " << multi_thread_state.sharedState.load() << std::endl;
}