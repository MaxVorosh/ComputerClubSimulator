#pragma once

class Table {
public:
    Table(int cost);
    void acquire(int time);
    void release(int time);
    int getIncome();
    int getUseTime();
    bool isFree();
private:
    int income;
    bool free;
    int startTime;
    int cost;
    int useTime;
};