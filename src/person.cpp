#include <cstring>
#include "person.h"

Person::Person(int id, std::string name) {
    this->id = id;
    this->name = name;
}

bool operator<(Person a, Person b) {
    int cmpRes = std::strcmp(a.name.c_str(), b.name.c_str());
    return cmpRes < 0 || (cmpRes == 0 && a.id < b.id);
}