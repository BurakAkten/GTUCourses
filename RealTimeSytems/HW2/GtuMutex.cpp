#include <iostream>
#include "GtuMutex.h"

#define ONE 1
using namespace std;

namespace gtu
{

GtuMutex::GtuMutex() { this->lockVariable = 0; }

GtuMutex::~GtuMutex()
{
}

void GtuMutex::lock()
{
    int index = getIndexOfThread(this_thread::get_id());
    if (index != NOT_REGISTERED && getThreadStatus(index))
    {

#ifdef WINDOWS
        for (; this->lockVariable == ONE ||
               InterlockedCompareExchange(&this->lockVariable, 1, 0) == ONE;)
        {
        }
#endif
#ifdef LINUX
        for (; this->lockVariable == ONE ||
               __sync_lock_test_and_set(&this->lockVariable, 1) == ONE;)
        {
        }
#endif
    }
}

void GtuMutex::unlock()
{
    this->lockVariable == 0;
    UNLOCK_MY_MUTEX(this->lockVariable)
}

void GtuMutex::registerMutex(std::thread::id thread_id, int prority)
{
    Helper helper;
    helper.worker_thread = thread_id;
    helper.priority = prority;
    helper.isBlocking = false;

    workers.push_back(helper);

    int index = getIndexOfThread(this_thread::get_id());
    setThreadStatus(index);
}

int GtuMutex::getIndexOfThread(std::thread::id thread_id)
{
    bool found = false;
    gtu::Helper registered;
    for (int i = 0; i < workers.size(); i++)
    {
        if (workers[i].worker_thread == std::this_thread::get_id())
        {
            return i;
        }
    }

    return NOT_REGISTERED;
}
void GtuMutex::setIndexOfThread(int index, int priorty)
{
    (workers[index]).priority = priorty;
}

bool GtuMutex::isThreadBlocking(int index)
{
    return workers[index].isBlocking;
}

int GtuMutex::getIndexOfBlockedThread()
{

    for (int i = 0; i < workers.size(); i++)
    {
        if (workers[i].isBlocking)
        {
            return i;
        }
    }

    return -1;
}

void GtuMutex::setThreadStatus(int index)
{
    if (workers.size() == 1)
    {
        return;
    }
    else
    {
        int biggestPriorityIndex = -1;
        int workingThreadIndex = -1;
        for (size_t i = 0; i < workers.size(); i++)
        {
            if (i != index && workers[i].priority > workers[index].priority)
            {
                biggestPriorityIndex = i;
                workers[index].isBlocking = false;
            }

            if (i != index && !workers[i].isBlocking)
            {
                workingThreadIndex = i;
            }
        }
        if (biggestPriorityIndex == -1)
        {
            workers[index].isBlocking = true;

            if (workingThreadIndex != -1)
            {
                workers[workingThreadIndex].priority = workers[index].priority;
                workers[workingThreadIndex].isBlocking = false;
            }
        }
    }
}

bool GtuMutex::getThreadStatus(int index)
{
    return workers[index].isBlocking;
}

} // namespace gtu