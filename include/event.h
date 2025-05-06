#include <string>

#pragma once

class Event {
public:
    virtual std::string to_string() = 0;
};

class EventForceGone : public Event {
public:
    EventForceGone(int time, std::string name);
    std::string to_string() override;
private:
    int time;
    std::string name;
};

class EventSitFromQueue : public Event {
public:
    EventSitFromQueue(int time, std::string name, int table);
    std::string to_string() override;
private:
    int time;
    std::string name;
    int table;
};

class EventError : public Event {
public:
    EventError(int time, std::string name);
    std::string to_string() override;
private:
    int time;
    std::string error;
};
    