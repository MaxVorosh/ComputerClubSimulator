#include <string>
#include <vector>
#include <map>
#include <queue>
#include "table.h"
#include "person.h"
#include "event.h"
#include "clientQueue.h"

#pragma once

class Club {
public:
    Club(int startTime, int endTime, int tablesN, int cost);
    ~Club();
    void addClient(int time, std::string name);
    void moveClient(int time, std::string name, int table);
    void waitClient(int time, std::string name);
    void dropClient(int time, std::string name);
    void addEvent(Event* event);
    void close();
private:
    std::vector<Table> tables;
    std::map<Person, int> busy_tables;
    std::map<std::string, int> guestsIds;
    ClientQueue line;
    std::vector<Event*> events;
    int startTime;
    int endTime;
    int newId;
};