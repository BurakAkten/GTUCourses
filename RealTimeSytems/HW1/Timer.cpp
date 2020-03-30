#include "Timer.h"

Timer::Timer()
{
    ready = false;
    timerThread = thread([this] {
        std::unique_lock<std::mutex> mlock(mtx_var);
        m_condVar.wait(mlock, std::bind(&Timer::isDataLoaded, this));
        while (works.size() > 0)
        {
            for (int i = 0; i < works.size(); i++)
            {
                Helper helper = works[i];
                switch (helper.rf)
                {
                case R1:
                {
                    chrono::duration<double, std::milli> time = helper.atTime - CLOCK::now();
                    if (time.count() <= 0.0)
                    {
                        R1_Func(helper);
                        works.erase(works.begin() + i);
                    }
                }
                break;
                case R2:
                {
                    chrono::duration<double, std::milli> time = helper.atTime - CLOCK::now();
                    if (time.count() <= 0.0)
                    {
                        R2_Func(helper);
                    }
                }
                break;
                case R3:
                {
                    chrono::duration<double, std::milli> time = helper.atTime - CLOCK::now();
                    if (time.count() <= 0.0)
                    {
                        if (R3_Func(helper))
                            works.erase(works.begin() + i);
                    }
                }
                break;
                case R4:
                {
                    chrono::duration<double, std::milli> time = helper.atTime - CLOCK::now();
                    if (time.count() <= 0.0)
                    {
                        if (R4_Func(helper))
                            works.erase(works.begin() + i);
                    }
                }
                break;
                default:
                    break;
                }
            }
        }
    });
}

void Timer::R1_Func(Helper helper)
{
    Timepoint start = CLOCK::now();
    helper.cb();
    Timepoint end = CLOCK::now();
    chrono::duration<double, std::milli> duration2 = end - start;

    if (duration2.count() > DURATION_MILISEC)
    {
        cout << "Deadline Error! (Late)\n";
    }
    else if (duration2.count() < DURATION_MILISEC)
    {
        cout << "Deadline Error! (Early)\n";
    }
    cout << "Duration (milliseconds): " << duration2.count() << endl
         << endl;
}

void Timer::R2_Func(Helper &helper)
{
    Timepoint start, end;
    Timepoint timerStart, timerEnd;

    start = CLOCK::now();
    helper.cb();
    end = CLOCK::now();
    chrono::duration<double, std::milli> duration = (end - start);

    helper.atTime = CLOCK::now() + (helper.period - (end - start));
    if (duration.count() > DURATION_MILISEC)
    {
        cout << "Deadline Error! (Late)\n";
    }
    else if (duration.count() < DURATION_MILISEC)
    {
        cout << "Deadline Error! (Early)\n";
    }
    cout << "Duration (milliseconds): " << duration.count() << endl
         << endl;
}

bool Timer::R3_Func(Helper &helper)
{
    Timepoint end, start2;

    chrono::duration<double, std::milli> duration = helper.tillTime - CLOCK::now();
    if (duration.count() >= 0.0)
    {
        start2 = CLOCK::now();
        helper.cb();
        end = CLOCK::now();
        chrono::duration<double, std::milli> duration2 = end - start2;

        helper.atTime = CLOCK::now() + (helper.period - (end - start2));
        if (duration2.count() > DURATION_MILISEC)
        {
            cout << "Deadline Error! (Late)\n";
        }
        else if (duration2.count() < DURATION_MILISEC)
        {
            cout << "Deadline Error! (Early)\n";
        }
        cout << "Duration (milliseconds): " << duration2.count() << endl
             << endl;

        return false;
    }
    else
    {
        return true;
    }
}

bool Timer::R4_Func(Helper &helper)
{
    Timepoint start, end;

    if (helper.predicate())
    {
        start = CLOCK::now();
        helper.cb();
        end = CLOCK::now();
        chrono::duration<double, std::milli> duration = end - start;
        helper.atTime = CLOCK::now() + (helper.period - (end - start));
        if (duration.count() > DURATION_MILISEC)
        {
            cout << "Deadline Error! (Late)\n";
        }
        else if (duration.count() < DURATION_MILISEC)
        {
            cout << "Deadline Error! (Early)\n";
        }
        cout << "Duration (milliseconds): " << duration.count() << endl
             << endl;

        return false;
    }
    else
    {
        return true;
    }
}

bool Timer::isDataLoaded()
{
    return ready;
}
// run the callback once at time point tp.
void Timer::registerTimer(const Timepoint &tp, const TTimerCallback &cb)
{

    Helper helper;
    helper.atTime = tp;
    helper.cb = cb;
    helper.rf = R1;

    works.push_back(helper);

    std::lock_guard<std::mutex> guard(mtx_var);

    ready = true;
    m_condVar.notify_all();
}

// run the callback periodically forever. The first call will be executed as soon as this callback is registered.
void Timer::registerTimer(const Millisecs &period, const TTimerCallback &cb)
{

    Helper helper;
    helper.atTime = CLOCK::now();
    helper.period = period;
    helper.cb = cb;
    helper.rf = R2;

    works.push_back(helper);

    std::lock_guard<std::mutex> guard(mtx_var);

    ready = true;

    m_condVar.notify_all();
}

// Run the callback periodically until time point tp. The first call will be executed as soon as this callback is
//registered.
void Timer::registerTimer(const Timepoint &tp, const Millisecs &period, const TTimerCallback &cb)
{
    Helper helper;
    helper.atTime = CLOCK::now();
    helper.period = period;
    helper.cb = cb;
    helper.tillTime = tp;
    helper.rf = R3;

    works.push_back(helper);

    std::lock_guard<std::mutex> guard(mtx_var);

    ready = true;

    m_condVar.notify_all();
}

// Run the callback periodically. Before calling the callback every time, call the predicate first to check if the
//termination criterion is satisfied. If the predicate returns false, stop calling the callback.
void Timer::registerTimer(const TPredicate &pred, const Millisecs &period, const TTimerCallback &cb)
{
    Helper helper;
    helper.predicate = pred;
    helper.cb = cb;
    helper.atTime = CLOCK::now();
    helper.rf = R4;
    helper.period = period;

    works.push_back(helper);

    std::lock_guard<std::mutex> guard(mtx_var);

    ready = true;
    m_condVar.notify_all();
}

Timer::~Timer()
{
    if (timerThread.joinable())
    {
        timerThread.join();
    }
}