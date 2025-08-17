#include "pch.h"
#include "iMutexies.h"

namespace HYDRA15::Foundation::Labourer
{
    void WriteFirstMutex::lock()
    {
        std::unique_lock<std::mutex> lk(mutex);

        waitingWriters++;
        writeCond.wait(lk, [this]() { return activeReaders == 0 && activeWriters == 0; });

        waitingWriters--;
        activeWriters = true;
    }

    void WriteFirstMutex::unlock()
    {
        std::unique_lock<std::mutex> lk(mutex);

        activeWriters = false;

        if (waitingWriters > 0)
            writeCond.notify_one();
        else
            readCond.notify_all();
    }

    bool WriteFirstMutex::try_lock()
    {
        std::unique_lock<std::mutex> lk(mutex);

        if (activeReaders == 0 && activeWriters == 0)
        {
            activeWriters = true;
            return true;
        }
        return false;
    }

    void WriteFirstMutex::lock_shared()
    {
        std::unique_lock<std::mutex> lk(mutex);

        readCond.wait(lk, [this]() { return waitingWriters == 0 && activeWriters == 0; });

        activeReaders++;
    }

    void WriteFirstMutex::unlock_shared()
    {
        std::unique_lock<std::mutex> lk(mutex);

        activeReaders--;

        if (activeReaders == 0 && waitingWriters > 0)
            writeCond.notify_one();
    }

    bool WriteFirstMutex::try_lock_shared()
    {
        std::unique_lock<std::mutex> lk(mutex);

        if (waitingWriters == 0 && activeWriters == 0)
        {
            activeReaders++;
            return true;
        }
        return false;
    }
}