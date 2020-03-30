#include <iostream>
#include <random>
#include "Timer.h"
using namespace std;

void test_function1();
void test_function2();
void test_function3();
void test_function4();
void test_function5();

bool predicateFunc();

int main()
{
    // Three first registerTimer function tested at the same time.
    //test_function1();

    // Two First registerTimer and one third registerTimer functions tested
    // at the same time.
    //test_function2();

    // Two first registerTimer, one second registerTimer, one third registerTimer,
    // one forth registerTimer functions tested at the same time.
    //test_function3();

    // One first registerTimer, one second registerTimer, one third regsiterTimer,
    // one fourth registerTimer functions tested at the same time.
    test_function4();

    //Two second registerTimer functions tested at the same  time;
    //test_function5();

    return 0;
}

// Three first registerTimer function tested at the same time.
void test_function1()
{

    Timepoint tp1 = std::chrono::system_clock::now() + std::chrono::seconds(3);
    Timepoint tp2 = std::chrono::system_clock::now() + std::chrono::seconds(1);
    Timepoint tp3 = std::chrono::system_clock::now() + std::chrono::seconds(2);
    Timer test;

    test.registerTimer(tp1, [] {
        cout << "Test1- Hello from callback (foo1)!" << endl;
    });
    test.registerTimer(tp2, [] {
        for (size_t i = 0; i < 10000; i++)
        {
            cout << "Test1- Hello from callback (foo2)!" << endl;
        }
    });

    test.registerTimer(tp3, [] {
        cout << "Test1- Hello from callback (foo3)!" << endl;
    });
}
// Two First registerTimer and one third registerTimer functions tested.
void test_function2()
{

    Timepoint tp1 = std::chrono::system_clock::now() + std::chrono::seconds(3);
    Timepoint tp2 = std::chrono::system_clock::now() + std::chrono::seconds(1);
    Timepoint tp3 = std::chrono::system_clock::now() + std::chrono::seconds(2);
    Millisecs period = Millisecs(10);
    Timer test;

    test.registerTimer(tp1, [] {
        cout << "Test2- Hello from callback (foo4)!" << endl;
    });
    test.registerTimer(tp2, [] {
        cout << "Test2- Hello from callback (foo5)!" << endl;
    });
    test.registerTimer(tp3, period, [] {
        cout << "Test2- Hello from callback (foo6)!" << endl;
    });
}

// Two first registerTimer, one second registerTimer, one third registerTimer,
// one forth registerTimer functions tested.
void test_function3()
{
    Timepoint tp1 = std::chrono::system_clock::now() + std::chrono::seconds(3);
    Timepoint tp2 = std::chrono::system_clock::now() + std::chrono::seconds(1);
    Timepoint tp3 = std::chrono::system_clock::now() + std::chrono::seconds(2);
    Millisecs period = Millisecs(10);
    Timer test;

    test.registerTimer(tp1, [] {
        cout << "Test3- Hello from callback (foo7)!" << endl;
    });
    test.registerTimer(tp2, [] {
        for (size_t i = 0; i < 10; i++)
        {
            cout << "Test3- Hello from callback (foo8)!" << endl;
        }
    });

    test.registerTimer(period, [] {
        cout << "Test3- Hello from callback (foo9 - infinite)!" << endl;
    });

    test.registerTimer(tp3, period, [] {
        cout << "Test2- Hello from callback (foo10)!" << endl;
    });

    test.registerTimer(predicateFunc, period, [] {
        cout << "Hello from callback (foo11)!" << endl;
    });
}

// One first registerTimer, one second registerTimer, one third regsiterTimer,
// one fourth registerTimer functions tested.
void test_function4()
{
    Timepoint tp1 = std::chrono::system_clock::now() + std::chrono::seconds(1);
    Timepoint tp3 = std::chrono::system_clock::now() + std::chrono::seconds(2);
    Millisecs period = Millisecs(10), period2 = Millisecs(20);
    Timer test;

    test.registerTimer(tp1, [] {
        for (size_t i = 0; i < 20; i++)
        {
            cout << "Test4- Hello from callback (foo12)!" << endl;
        }
    });

    test.registerTimer(period, [] {
        cout << "Test4- Hello from callback (foo13 - infinite)!" << endl;
    });

    test.registerTimer(tp3, period, [] {
        cout << "Test4- Hello from callback (foo14)!" << endl;
    });

    test.registerTimer(predicateFunc, period, [] {
        cout << "Test4- Hello from callback (foo15)!" << endl;
    });
}

//Two second registerTimer functions tested at the same  time;
void test_function5()
{
    Millisecs period = Millisecs(10), period2 = Millisecs(20);
    Timer test;

    test.registerTimer(period, [] {
        cout << "Test5- Hello from callback (foo16 - infinite)!" << endl;
    });

    test.registerTimer(period2, [] {
        cout << "Test5- Hello from callback (foo17 - infinite)!" << endl;
    });
}

bool predicateFunc()
{
    random_device randDevice;

    mt19937 mt(randDevice());

    uniform_int_distribution<int> intDist(1, 1000);

    int rand = intDist(mt);

    cout << "Returned " << (rand % 2 == 0 ? "true" : "false") << " from predicate!" << endl
         << endl;

    return rand % 2 == 0 ? true : false;
}
