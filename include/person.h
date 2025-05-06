#include <string>

#pragma once

struct Person {
    int id;
    std::string name;

    Person() = default;
    Person(int id, std::string name);
};

bool operator<(Person a, Person b);