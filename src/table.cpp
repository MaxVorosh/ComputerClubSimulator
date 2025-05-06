#include <stdexcept>
#include "table.h"

Table::Table(int cost) {
    this->cost = cost;
    income = 0;
    free = true;
    useTime = 0;
    startTime = -1;
}

void Table::acquire(int time) {
    if (!free) {
        throw std::runtime_error("Table is not empty");
    }
    startTime = time;
    free = false;
}

void Table::release(int time) {
    if (free) {
        throw std::runtime_error("Table is free");
    }
    if (time < startTime) {
        throw std::runtime_error("Negative time difference");
    }
    free = true;
    int diff = time - startTime;
    useTime += diff;
    int h = diff / 60;
    if (diff % 60 != 0) {
        h++;
    }
    income += h * cost;
    startTime = -1;
}

int Table::getIncome() {
    return income;
}

int Table::getUseTime() {
    return useTime;
}

bool Table::isFree() {
    return free;
}
