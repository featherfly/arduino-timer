#ifndef SOFTWARE_TIMER_H
#define SOFTWARE_TIMER_H

#include <stdint.h>
#include <stdbool.h>

class TimeoutTimer
{
private:
    unsigned long _start = 0;
    uint32_t _timeout;
    uint32_t _runningTime = 0;
    void (*user_onTimeout)(uint32_t running_time);

public:
    TimeoutTimer();

    TimeoutTimer(uint32_t timeout);
    /**
     * @brief start timer
     */
    void start();
    /**
     * @brief reset timer
     */
    void reset();
    /**
     * @brief stop timer 
     */
    void stop();
    /**
     * @brief get runnning state
     * 
     * @return true is running invoke start method
     * @return false is not running invoke stop method
     */
    bool is_running();
    /**
     * @brief Set the timeout value
     * 
     * @param timeout timeout value
     */
    void set_timeout(uint32_t timeout);
    /**
     * @brief get is timeout state
     * 
     * @return true timeout
     * @return false not timeout
     */
    bool is_timeout();
    /**
     * @brief get is timeout state
     * 
     * @param timeout timeout value
     * @return true timeout
     * @return false not timeout 
     */
    bool is_timeout(uint32_t timeout);
    /**
     * @brief set timeout event listener
     */
    void on_timeout(void (*)(uint32_t running_time));
    /**
     * @brief dispatch timeout event
     */
    void dispatch_timeout_event();

    uint32_t running_time();
};

#endif