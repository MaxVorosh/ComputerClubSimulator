#include <map>
#include "person.h"

#pragma once

class ClientQueue {
public:
    ClientQueue();
    bool in(Person p);
    void push(Person p);
    void pop(Person p);
    Person popLeft();
    int size();
private:
    std::map<int, Person> persons;
    std::map<Person, int> positions;
    int lastPos;
};