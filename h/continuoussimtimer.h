/**
 * @file continuoussimtimer.h
 * @author Sawyer Stanley (sawyerscoding@gmail.com)
 * @brief ContinuousSimTimers are used for updating Updateable objects at regular real-world time intervals.
 * @version 0.1
 * @date 2023-11-02
 */

#ifndef CONTINUOUSSIMTIMER_H
#define CONTINUOUSSIMTIMER_H

#include <iostream>
#include <unordered_set>
#include <queue>
#include <thread>
#include "updateable.h"

#if BUILD_PLATFORM == WINDOWS_BUILD
#include <windows.h>
#elif BUILD_PLATFORM == LINUX_BUILD
#include <unistd.h>
#define Sleep(milli) usleep(milli)
#endif

class ContinuousSimTimer{

    private:
    bool isPaused;
    unsigned long long totalMillisecondsElapsed;
    unsigned long long updateTimeInSeconds;
    unsigned long long seconds;
    unsigned long long minutes;
    unsigned long long hours;
    std::unordered_set<Updateable*> updateables;
    std::queue<std::thread*> activeThreads;

    public:
    /// @brief Creates a Continuous Simulation Timer that updates all simulation entities at regular real-world time
    /// intervals.
    /// @param updateTimeInSeconds The real-world time interval in seconds at which the timer will update simulation 
    /// entities. 
    ContinuousSimTimer(double updateTimeInSeconds);
    ~ContinuousSimTimer();

    public:
    /// @brief Starts the timer. If the timer was paused, the timer will continue from when it was last paused.
    void start();
    /// @brief Pauses the timer without reseting the overall time elapsed.
    void pause();
    /// @brief Pauses the timer and resets the overall time elapsed to 0.
    void reset();
    /// @brief Gets whether the timer is currently paused.
    /// @return True if the timer is paused.
    bool getIsPaused();
    /// @brief Gets the number of hours the timer has been running.
    /// @return The number of hours the timer has been running.
    unsigned long long getHours();
    /// @brief Gets the number of minutes the timer has been running.
    /// @return The number of minutes the timer has been running.
    unsigned long long getMinutes();
    /// @brief Gets the number of seconds the timer has been running.
    /// @return The number of seconds the timer has been running.
    unsigned long long getSeconds();
    /// @brief Gets the number of milliseconds the timer has been running.
    /// @return The number of milliseconds the timer has been running.
    unsigned long long getMilliseconds();
    /// @brief Get the real-world time interval in seconds at which the timer updates simulation entities.
    /// @return The real-world time interval in seconds at which the timer updates simulation entities.
    double getUpdateTimeInSeconds();
    /// @brief Add a new entity to be updated at regular real-world time intervals.
    /// @param updateable 
    void addUpdatable(Updateable *updateable);

    private:
    /// @brief Updates all updateables asyncronously.
    void asyncUpdateUpdateables();
    /// @brief Suspends timer until all updateables have been updated.
    void waitForUpdate();

};

#endif // CONTINUOUSSIMTIMER_H