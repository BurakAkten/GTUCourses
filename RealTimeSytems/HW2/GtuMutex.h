
#ifdef _WIN32
#include <Windows.h>
#define WINDOWS
#elif defined(_WIN64)
#include <Windows.h>
#define WINDOWS
#elif defined(unix) || defined(__unix__) || defined(__unix) || defined(__linux)
#include <unistd.h>
#define LINUX
#endif

#ifdef WINDOWS
#define UNLOCK_MY_MUTEX(x) WindowsUnlockCode(x)
#endif
#ifdef LINUX
#define UNLOCK_MY_MUTEX(x) \
    do                     \
    {                      \
    } while (false);
#endif

#include <vector>
#include <thread>
#define NOT_REGISTERED -999
namespace gtu
{

class Helper
{
public:
    std::thread::id worker_thread;
    int priority;
    bool isBlocking;
};

class GtuMutex
{
private:
    std::vector<gtu::Helper> workers;
    volatile unsigned long lockVariable;

    int getIndexOfThread(std::thread::id thread_id);
    void setIndexOfThread(int index, int priorty);
    bool isThreadBlocking(int index);
    int getIndexOfBlockedThread();
    void setThreadStatus(int index);
    bool getThreadStatus(int index);

public:
    GtuMutex();
    ~GtuMutex();
    void registerMutex(std::thread::id thread_id, int prority);
    void lock();
    void unlock();
};
}; // namespace gtu