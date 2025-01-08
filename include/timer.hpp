/**
 * @file timer.hpp
 * @author ArtemK
 * @brief Class to work with time
 * @version 0.1
 * @date 2025-01-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __CUSTOM_TIMER__
#define __CUSTOM_TIMER__

#include <SDL3/SDL.h>
#include "common/types.hpp"


class Timer {
public:
    constexpr Timer() = default;
    constexpr Timer(uint64 nanosecond)
    : m_offsetTickNs(nanosecond)
    , m_isRunning(false)
    , m_isPaused(false) {}
    constexpr Timer(Timer&&) = default;
    
    Timer& operator=(const Timer&) = delete;
    Timer(const Timer&) = delete;
    Timer& operator=(Timer&&) = delete;

    ~Timer() = default;

    [[nodiscard]] constexpr 
    uint64 getElapsedTime() const {
        const uint64 carry = m_isPaused ? m_idleTickNs - m_startTickNs : SDL_GetTicksNS() - m_startTickNs;
        const uint64 retVal = m_offsetTickNs + m_totalTickNs + carry;
        return retVal;
    }

    [[nodiscard]] constexpr
    bool isRunning() const {
        return m_isRunning;
    }

    [[nodiscard]] constexpr
    bool isPaused() const {
        return m_isPaused;
    }

    constexpr
    void start();

    constexpr
    void stop();

    constexpr
    void restart();

    constexpr
    void pause();

    constexpr
    void unpause();


private:
    const uint64 m_offsetTickNs{0};

    uint64 m_startTickNs{0};
    uint64 m_idleTickNs {0};
    uint64 m_totalTickNs{0};

    bool m_isRunning{false};
    bool m_isPaused {false};
};

constexpr
void Timer::start() {
    if(m_isRunning || m_isPaused)  /* if timer is active or paused => return */
        return;

    m_isRunning = true;
    m_startTickNs = SDL_GetTicksNS();
}

constexpr
void Timer::stop() {
    if(!m_isRunning)  /* if timer isn't active => return. !(true) == false*/
        return;

    m_isRunning = false;

    m_startTickNs = 0;
    m_idleTickNs  = 0;
    m_totalTickNs = 0;
}

constexpr
void Timer::pause() {
    if(!m_isRunning || m_isPaused)  /* if timer ISN'T active or IS paused => return. !(true) == false*/
        return;

    m_isPaused = true;

    m_idleTickNs = SDL_GetTicksNS();
}

constexpr
void Timer::unpause() {
    if(!m_isRunning || !m_isPaused)  /* if timer ISN'T active or ISN'T paused => return. !(true) == false*/
        return;

    m_isPaused = false;

    m_totalTickNs += m_idleTickNs - m_startTickNs;
    m_idleTickNs = 0;
    m_startTickNs = SDL_GetTicksNS();
}

constexpr
void Timer::restart() {
    if(!m_isRunning)  /* if timer ISN'T active => return. !(true) == false*/
        return;

    m_isPaused = false;

    m_startTickNs = 0;
    m_idleTickNs  = 0;
    m_totalTickNs = 0;
}


#endif  // !__CUSTOM_TIMER__
