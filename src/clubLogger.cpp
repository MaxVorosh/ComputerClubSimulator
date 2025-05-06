#include "clubLogger.h"

ClubLogger::ClubLogger(int startTime, int endTime, int tablesN, int cost) {
    club = new Club(startTime, endTime, tablesN, cost);
}

ClubLogger::~ClubLogger() {
    delete club;
}

void ClubLogger::processEvent(IncomeEvent* ev) {
    club->addEvent(ev);
    ev->visit(club);
}

void ClubLogger::close() {
    club->close();
}

std::vector<Table>* ClubLogger::getProfit() {
    return club->getProfit();
}

std::vector<Event*>* ClubLogger::getEvents() {
    return club->getEvents();
}