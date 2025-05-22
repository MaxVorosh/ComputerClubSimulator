#include <vector>
#include <string>
#include <fstream>
#include "clubLogger.h"

#pragma once

class Parser {
public:
    Parser() = default;
    void parse(std::string filename, std::vector<std::string>& outLines);
    bool checkDecimal(const std::string& number);
    bool checkName(const std::string& name);
private:
    bool parseEvents(std::ifstream& fin, std::vector<std::string>& outLines, ClubLogger* club);
    void writeEvents(std::vector<std::string>& outLines, ClubLogger* club);
    void writeProfit(std::vector<std::string>& outLines, ClubLogger* club);
    void writeError(std::vector<std::string>& outLines, std::string line);
};