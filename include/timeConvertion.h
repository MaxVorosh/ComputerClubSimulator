#include <string>
#include <stdexcept>

#pragma once

std::string timeToStr(int time) {
    int h = time / 60;
    int m = time % 60;
    std::string hStr = std::to_string(h);
    std::string mStr = std::to_string(m);
    if (hStr.size() == 1) {
        hStr = "0" + hStr;
    }
    if (mStr.size() == 1) {
        mStr = "0" + mStr;
    }
    return hStr + ":" + mStr;
}

int strToTime(std::string time) {
    if (time.size() != 5) {
        throw std::runtime_error("Wrong time format");
    }
    int h = std::atoi(time.substr(0, 2).c_str());
    int m = std::atoi(time.substr(3, 2).c_str());
    return h * 60 + m;
}