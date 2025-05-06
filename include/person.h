#include <string>

#pragma once

struct Person {
    int id;
    std::string name;

    Person(int id, std::string name);
};

bool operator<(Person a, Person b);