#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <atomic>
#include <iterator>
#include "ITimer.h"

#define DURATION_MILISEC 5.0

using namespace std;

enum RegisterFunc
{
    R1,
    R2,
    R3,
    R4
};

class Helper
{
public:
    RegisterFunc rf;
    Timepoint atTime;
    TTimerCallback cb;
    Timepoint tillTime;
    Millisecs period;
    TPredicate predicate;
};

class Timer : public ITimer
{

private:
    thread timerThread;
    mutex mtx_var;
    condition_variable m_condVar;
    vector<Helper> works;
    atomic_bool ready = ATOMIC_VAR_INIT(true);

    // make works for registerTimer(const Timepoint &tp, const TTimerCallback &cb);
    void R1_Func(Helper helper);

    // make works for registerTimer(const Millisecs &period, const TTimerCallback &cb);
    void R2_Func(Helper &helper);

    // make works for registerTimer(const Timepoint &tp, const Millisecs &period, const TTimerCallback &cb);
    bool R3_Func(Helper &helper);

    // make works for registerTimer(const TPredicate &pred, const Millisecs &period, const TTimerCallback &cb);
    bool R4_Func(Helper &helper);

    //return the current value of ready variable
    bool isDataLoaded();

public:
    Timer();

    // run the callback once at time point tp.
    void registerTimer(const Timepoint &tp, const TTimerCallback &cb);

    // run the callback periodically forever. The first call will be executed as soon as this callback is registered.
    void registerTimer(const Millisecs &period, const TTimerCallback &cb);

    // Run the callback periodically until time point tp. The first call will be executed as soon as this callback is
    //registered.
    void registerTimer(const Timepoint &tp, const Millisecs &period, const TTimerCallback &cb);

    // Run the callback periodically. Before calling the callback every time, call the predicate first to check if the
    //termination criterion is satisfied. If the predicate returns false, stop calling the callback.
    void registerTimer(const TPredicate &pred, const Millisecs &period, const TTimerCallback &cb);

    ~Timer();
};
