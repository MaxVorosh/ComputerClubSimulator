#include "club.h"
#include "incomeEvent.h"

#pragma once

class ClubLogger {
public:
    ClubLogger(int startTime, int endTime, int tablesN, int cost);
    ~ClubLogger();
    void processEvent(IncomeEvent* ev);
    void close();

    std::vector<Table>* getProfit();
    std::vector<Event*>* getEvents();
private:
    Club* club;
};