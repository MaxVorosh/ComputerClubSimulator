#include "club.h"

Club::Club(int startTime, int endTime, int tablesN, int cost) {
    this->startTime = startTime;
    this->endTime = endTime;
    tables.resize(tablesN, Table(cost));
    newId = 0;
}

Club::~Club() {
    for (int i = 0; i < events.size(); ++i) {
        delete events[i];
    }
}

void Club::addClient(int time, std::string name) {
    if (time < startTime || time > endTime) {
        EventError* err = new EventError(time, "NotOpenYet");
        addEvent(err);
        return;
    }
    if (guestsIds.find(name) != guestsIds.end()) {
        EventError* err = new EventError(time, "YouShallNotPass");
        addEvent(err);
        return;
    }
    Person client(newId, name);
    newId++;
    guestsIds[client.name] = client.id;
}

void Club::moveClient(int time, std::string name, int table) {
    if (guestsIds.find(name) == guestsIds.end()) {
        EventError* err = new EventError(time, "ClientUnknown");
        addEvent(err);
        return;
    }
    if (!tables[table].isFree()) {
        EventError* err = new EventError(time, "PlaceIsBusy");
        addEvent(err);
        return;
    }
    int id = guestsIds[name];
    Person client(id, name);
    if (busy_tables.find(client) != busy_tables.end()) {
        int tableFrom = busy_tables[client];
        tables[tableFrom].release(time);
    }
    line.pop(client);
    tables[table].acquire(time);
    busy_tables[client] = table;
}

void Club::waitClient(int time, std::string name) {
    if (guestsIds.find(name) == guestsIds.end()) {
        EventError* err = new EventError(time, "ClientUnknown");
        addEvent(err);
        return;
    }

    int id = guestsIds[name];
    Person client(id, name);

    if (busy_tables.size() != tables.size() || busy_tables.find(client) != busy_tables.end()) {
        EventError* err = new EventError(time, "ICanWaitNoLonger!");
        addEvent(err);
        return;
    }
    if (line.size() > tables.size()) {
        EventForceGone* ev = new EventForceGone(time, name);
        addEvent(ev);
        dropClient(time, name);
        return;
    }
    line.push(client);
}

void Club::dropClient(int time, std::string name) {
    if (guestsIds.find(name) == guestsIds.end()) {
        EventError* err = new EventError(time, "ClientUnknown");
        addEvent(err);
        return;
    }
    int id = guestsIds[name];
    Person client(id, name);
    if (busy_tables.find(client) != busy_tables.end()) {
        int table = busy_tables[client];
        tables[table].release(time);
        busy_tables.erase(client);
        if (line.size() > 0) {
            Person p = line.popLeft();
            busy_tables[p] = table;
            tables[table].acquire(time);
            EventSitFromQueue* ev = new EventSitFromQueue(time, p.name, table);
            addEvent(ev);
        }
        return;
    }
    line.pop(client);
    guestsIds.erase(name);
}

void Club::addEvent(Event* event) {
    events.push_back(event);
}

void Club::close() {
    for (auto p: busy_tables) {
        Person client = p.first;
        int table = p.second;
        EventForceGone* ev = new EventForceGone(endTime, client.name);
        addEvent(ev);
        tables[table].release(endTime);
    }
}

std::vector<Table>* Club::getProfit() {
    return &tables;
}

std::vector<Event*>* Club::getEvents() {
    return &events;
}