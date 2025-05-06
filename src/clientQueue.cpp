#include "clientQueue.h"

ClientQueue::ClientQueue() {
    lastPos = 0;
}

bool ClientQueue::in(Person p) {
    return positions.find(p) != positions.end();
}

void ClientQueue::pop(Person p) {
    if (!in(p)) {
        return;
    }
    int position = positions[p];
    positions.erase(p);
    persons.erase(position);
}

void ClientQueue::push(Person p) {
    if (in(p)) {
        return;
    }
    int position = lastPos;
    lastPos++;
    positions[p] = position;
    persons[position] = p;
}  

Person ClientQueue::popLeft() {
    Person p = (*persons.begin()).second;
    int position = (*persons.begin()).first;
    persons.erase(position);
    positions.erase(p);
    return p;
}

int ClientQueue::size() {
    return positions.size();
}