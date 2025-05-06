#include <sstream>
#include "incomeEvent.h"
#include "timeConvertion.h"

void EventCome::visit(Club* club) {
    club->addClient(time, name);
}

void EventSit::visit(Club* club) {
    club->moveClient(time, name, table);
}

void EventWait::visit(Club* club) {
    club->waitClient(time, name);
}

void EventGone::visit(Club* club) {
    club->dropClient(time, name);
}

std::string EventCome::to_string() {
    std::stringstream sStream;
    sStream << timeToStr(time) << ' ' << 1 << ' ' << name;
    return sStream.str();
}

std::string EventSit::to_string() {
    std::stringstream sStream;
    sStream << timeToStr(time) << ' ' << 2 << ' ' << name << ' ' << table;
    return sStream.str();
}

std::string EventWait::to_string() {
    std::stringstream sStream;
    sStream << timeToStr(time) << ' ' << 3 << ' ' << name;
    return sStream.str();
}

std::string EventGone::to_string() {
    std::stringstream sStream;
    sStream << timeToStr(time) << ' ' << 4 << ' ' << name;
    return sStream.str();
}

EventCome::EventCome(int time, std::string name) {
    this->time = time;
    this->name = name;
}

EventSit::EventSit(int time, std::string name, int table) {
    this->time = time;
    this->name = name;
    this->table = table;
}

EventWait::EventWait(int time, std::string name) {
    this->time = time;
    this->name = name;
}

EventGone::EventGone(int time, std::string name) {
    this->time = time;
    this->name = name;
}