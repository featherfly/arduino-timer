#include "SoftWareTimer.h"

#include <arduino.h>

SoftWareTimer::SoftWareTimer() : SoftWareTimer(0) {}
SoftWareTimer::SoftWareTimer(uint32_t timeout) {
    set_timeout(timeout);
    on_timeout([](uint32_t times) {});  // 设置一个默认实现，防止指针空
}

void SoftWareTimer::start() { _start = millis(); }

void SoftWareTimer::reset() { _start = 1; }

bool SoftWareTimer::is_running() { return _start > 0; }

void SoftWareTimer::stop() {
    _start = 0;
    _runningTime = 0;
}

void SoftWareTimer::set_timeout(uint32_t timeout) { _timeout = timeout; }

bool SoftWareTimer::is_timeout() { return is_timeout(_timeout); }

bool SoftWareTimer::is_timeout(uint32_t timeout) {
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

uint32_t SoftWareTimer::running_time() { return _runningTime; }

void SoftWareTimer::on_timeout(void (*function)(uint32_t running_time)) {
    this->user_onTimeout = function;
}

void SoftWareTimer::dispatch_timeout_event() { user_onTimeout(_runningTime); }