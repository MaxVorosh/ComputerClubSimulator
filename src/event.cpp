#include <sstream>
#include "event.h"
#include "timeConvertion.h"

std::string EventForceGone::to_string() {
    std::stringstream sStream;
    sStream << timeToStr(time) << ' ' << 11 << ' ' << name;
    return sStream.str();
}

std::string EventSitFromQueue::to_string() {
    std::stringstream sStream;
    sStream << timeToStr(time) << ' ' << 12 << ' ' << name << ' ' << table + 1;
    return sStream.str();
}

std::string EventError::to_string() {
    std::stringstream sStream;
    sStream << timeToStr(time) << ' ' << 13 << ' ' << error;
    return sStream.str();
}

EventForceGone::EventForceGone(int time, std::string name) {
    this->time = time;
    this->name = name;
}

EventSitFromQueue::EventSitFromQueue(int time, std::string name, int table) {
    this->time = time;
    this->name = name;
    this->table = table;
}

EventError::EventError(int time, std::string error) {
    this->time = time;
    this->error = error;
}
