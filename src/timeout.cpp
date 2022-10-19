#include "timeout.h"

#include <arduino.h>

TimeoutTimer::TimeoutTimer() : TimeoutTimer(0) {}
TimeoutTimer::TimeoutTimer(uint32_t timeout) {
    set_timeout(timeout);
    on_timeout([](uint32_t times) {});  // 设置一个默认实现，防止指针空
}

void TimeoutTimer::start() { _start = millis(); }

void TimeoutTimer::reset() { _start = 1; }

bool TimeoutTimer::is_running() { return _start > 0; }

void TimeoutTimer::stop() {
    _start = 0;
    _runningTime = 0;
}

void TimeoutTimer::set_timeout(uint32_t timeout) { _timeout = timeout; }

bool TimeoutTimer::is_timeout() { return is_timeout(_timeout); }

bool TimeoutTimer::is_timeout(uint32_t timeout) {
    if (is_running()) {
        unsigned long current = millis();
        // inf << "current " << current << " timeout " << timeout << " start "
        // << _start << endl; uint32_t t = _start + timeout;
        unsigned long t = current - _start;
        // return current > _start + timeout;
        if (t > timeout) {
            // inf << "current " << current << " timeout " << timeout << " start
            // " << _start << endl;
            if (_runningTime == 0) {
                _runningTime = t;
            }
            return true;
        }
    }
    return false;
}

uint32_t TimeoutTimer::running_time() { return _runningTime; }

void TimeoutTimer::on_timeout(void (*function)(uint32_t running_time)) {
    this->user_onTimeout = function;
}

void TimeoutTimer::dispatch_timeout_event() { user_onTimeout(_runningTime); }