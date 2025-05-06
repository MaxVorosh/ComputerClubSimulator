#include "event.h"
#include "club.h"

#pragma once

class IncomeEvent : public Event {
public:
    virtual void visit(Club* club) = 0;
};

class EventCome : public IncomeEvent {
public:
    EventCome(int time, std::string name);
    void visit(Club* club) override;
    std::string to_string() override;
private:
    int time;
    std::string name;
};

class EventSit : public IncomeEvent {
public:
    EventSit(int time, std::string name, int table);
    void visit(Club* club) override;
    std::string to_string() override;
private:
    int time;
    std::string name;
    int table;
};

class EventWait : public IncomeEvent {
public:
    EventWait(int time, std::string name);
    void visit(Club* club) override;
    std::string to_string() override;
private:
    int time;
    std::string name;
};

class EventGone : public IncomeEvent {
public:
    EventGone(int time, std::string name);
    void visit(Club* club) override;
    std::string to_string() override;
private:
    int time;
    std::string name;
};