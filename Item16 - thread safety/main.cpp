#include <iostream>
#include <thread>
#include <future>
#include <vector>

// for making classes threadsafe we can use 
// - atomics
// - guards

// if a member function is const, it can still modify mutable data

class A 
{
public: 
    void GetCallCount_unstable () const 
    {
        // datarace!!
        callCount++;
    }

    mutable int callCount { 0 };
private: 
};

void RunTask (A& a) 
{
    a.GetCallCount_unstable ();
}

int main () 
{
    A a;
    std::vector<std::future<void>> threads;
    for (int i = 0; i < 2000; ++i) 
    {
        threads.push_back (std::async(std::launch::async, RunTask, std::ref(a)));
    }

    for (auto& t : threads) {
        t.get ();
    }

    std::cout << "final value: " << a.callCount << std::endl;

    return 0;
}