#include "clubLogger.h"

ClubLogger::ClubLogger(int startTime, int endTime, int tablesN, int cost) {
    club = new Club(startTime, endTime, tablesN, cost);
}

ClubLogger::~ClubLogger() {
    delete club;
}

void ClubLogger::processEvent(IncomeEvent* ev) {
    ev->visit(club);
}