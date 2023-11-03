#include "../h/continuoussimtimer.h"

ContinuousSimTimer::ContinuousSimTimer(double updateTimeInSeconds)
{
    this->updateTimeInSeconds = (unsigned long long)(updateTimeInSeconds * 100);
    reset();
    updateables.clear();
    while(!activeThreads.empty()){
        activeThreads.pop();
    }
}

ContinuousSimTimer::~ContinuousSimTimer()
{
    updateables.clear();
    while(!activeThreads.empty()){
        activeThreads.pop();
    }
}

void ContinuousSimTimer::start()
{
    isPaused = false;
    while(!isPaused){
        // Count timer
        totalMillisecondsElapsed++;

        if(totalMillisecondsElapsed % updateTimeInSeconds == 0){
            // Call sim update asyncronously
            waitForUpdate();
            asyncUpdateUpdateables();
        }

        if(totalMillisecondsElapsed % 100 == 0){
            seconds++;

            if(seconds == 60){
                minutes++;
                seconds = 0;
                if(minutes == 60){
                    hours++;
                    minutes = 0;
                }
            }
        }

        Sleep(1);
    }
}

void ContinuousSimTimer::pause()
{
    isPaused = true;
}

void ContinuousSimTimer::reset()
{
    pause();
    hours = 0;
    minutes = 0;
    seconds = 0;
    totalMillisecondsElapsed = 0;
}

bool ContinuousSimTimer::getIsPaused()
{
    return isPaused;
}

unsigned long long ContinuousSimTimer::getHours()
{
    return hours;
}

unsigned long long ContinuousSimTimer::getMinutes()
{
    return minutes;
}

unsigned long long ContinuousSimTimer::getSeconds()
{
    return seconds;
}

unsigned long long ContinuousSimTimer::getMilliseconds()
{
    return totalMillisecondsElapsed % 100;
}

double ContinuousSimTimer::getUpdateTimeInSeconds()
{
    return ((double)updateTimeInSeconds) / 100.0;
}

void ContinuousSimTimer::addUpdatable(Updateable *updateable)
{
    updateables.emplace(updateable);
}

void ContinuousSimTimer::asyncUpdateUpdateables()
{
    for(Updateable *u : updateables){
        std::thread *th = new std::thread(Updateable::update, u);
        activeThreads.emplace(th);
    }

}

void ContinuousSimTimer::waitForUpdate()
{
    while(!activeThreads.empty()){
        std::thread *cur = activeThreads.front();
        activeThreads.pop();
        cur->join();
        delete cur;
    }
}
