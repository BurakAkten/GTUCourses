#include <iostream>
#include <mutex>
#include <thread>
#include "GtuMutex.h"

using namespace gtu;
using namespace std;

void f(int num);
GtuMutex mutex1, mutex2;

int main(int argc, const char **argv)
{

    thread t1([] {
        mutex1.registerMutex(this_thread::get_id(), 20);
        std::lock_guard<gtu::GtuMutex> lck(mutex1);
        for (size_t i = 0; i < 1000; i++)
        {
            cout << "Test- Hello from callback (foo)!" << endl;
        }
    });

    thread t2([] {
        mutex2.registerMutex(this_thread::get_id(), 40);
        std::lock_guard<gtu::GtuMutex> lck(mutex2);
        for (size_t i = 0; i < 10000; i++)
        {
            cout << "Test- Hello from callback (foo1)!" << endl;
        }
    });

    t1.join();
    t2.join();

    return 0;
}