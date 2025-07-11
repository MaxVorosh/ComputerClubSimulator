#include <fstream>
#include <sstream>
#include "parser.h"
#include "timeConvertion.h"
#include "clubLogger.h"

void Parser::parse(std::string filename, std::vector<std::string>& outLines) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        throw std::runtime_error("File opening error");
    }
    std::string line;
    std::getline(fin, line);
    int tablesN = std::atoi(line.c_str());
    if (tablesN <= 0 || !checkDecimal(line)) {
        writeError(outLines, line);
        return;
    }
    std::getline(fin, line);
    std::stringstream sStream(line);
    std::string startTime, endTime;
    sStream >> startTime >> endTime;
    int realStartTime, realEndTime;
    try {
        realStartTime = strToTime(startTime);
        realEndTime = strToTime(endTime);
        std::string remains;
        sStream >> remains;
        if (realStartTime > realEndTime || remains.size() > 0) {
            writeError(outLines, line);
            return;
        }
    }
    catch (...) {
        writeError(outLines, line);
        return;
    }
    std::getline(fin, line);
    int cost = std::atoi(line.c_str());
    if (cost <= 0 || !checkDecimal(line)) {
        writeError(outLines, line);
        return;
    }
    ClubLogger club(realStartTime, realEndTime, tablesN, cost);
    bool goodParsing = parseEvents(fin, outLines, &club);
    if (!goodParsing) {
        return;
    }
    outLines.push_back(startTime);
    writeEvents(outLines, &club);
    outLines.push_back(endTime);
    writeProfit(outLines, &club);
    fin.close();
}

void Parser::writeError(std::vector<std::string>& outLines, std::string line) {
    outLines.clear();
    outLines.push_back(line);
}

bool Parser::parseEvents(std::ifstream& fin, std::vector<std::string>& outLines, ClubLogger* club) {
    std::string line;
    int lastTime = -1;
    while (std::getline(fin, line)) {
        std::stringstream sStream(line);
        std::string time, name;
        int type;
        sStream >> time >> type >> name;
        int realTime;
        try {
            realTime = strToTime(time);
        }
        catch (...) {
            writeError(outLines, line);
            return false;
        }
        if (realTime < lastTime || type < 1 || type > 4 || !checkName(name)) {
            writeError(outLines, line);
            return false;
        }
        lastTime = realTime;
        IncomeEvent* ev;
        if (type == 1) {
            ev = new EventCome(realTime, name);
        }
        else if (type == 2) {
            int table;
            sStream >> table;
            table--;
            if (table < 0 || table >= club->getProfit()->size()) {
                writeError(outLines, line);
                return false;
            }
            ev = new EventSit(realTime, name, table);
        }
        else if (type == 3) {
            ev = new EventWait(realTime, name);
        }
        else {
            ev = new EventGone(realTime, name);
        }
        if (sStream.fail()) {
            writeError(outLines, line);
            return false;
        }
        std::string remains;
        sStream >> remains;
        if (remains.size() > 0) {
            writeError(outLines, line);
            return false;
        }
        club->processEvent(ev);
    }
    club->close();
    return true;
}

void Parser::writeEvents(std::vector<std::string>& outLines, ClubLogger* club) {
    for (Event* ev : *(club->getEvents())) {
        outLines.push_back(ev->to_string());
    }
}

void Parser::writeProfit(std::vector<std::string>& outLines, ClubLogger* club) {
    auto tables = club->getProfit();
    for (int i = 0; i < tables->size(); ++i) {
        std::stringstream sStream;
        sStream << i + 1 << ' ' << tables->at(i).getIncome() << ' ' << timeToStr(tables->at(i).getUseTime());
        outLines.push_back(sStream.str());
    }
}

bool Parser::checkDecimal(const std::string& number) {
    int i = 0;
    if (number.size() > 0 && number[i] == '-') {
        i++;
    }
    for (; i < number.size(); ++i) {
        if ('0' > number[i] || number[i] > '9') {
            return false;
        }
    }
    return true;
}

bool Parser::checkName(const std::string& name) {
    for (int i = 0; i < name.size(); ++i) {
        if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= '0' && name[i] <= '9') || name[i] == '_' || name[i] == '-')) {
            return false;
        }
    }
    return true;
}