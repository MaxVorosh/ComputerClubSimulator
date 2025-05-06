#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "parser.h"
#include "timeConvertion.h"

#include <vector>


TEST_CASE("TimeConvertion test") {
    std::vector<std::string> correct = {"00:00", "16:37", "04:20", "23:59"};
    std::vector<int> answers = {0, 16 * 60 + 37, 4 * 60 + 20, 23 * 60 + 59};
    CHECK_THROWS(strToTime("1:23"));
    for (int i = 0; i < correct.size(); ++i) {
        CHECK(strToTime(correct[i]) == answers[i]);
        CHECK(correct[i] == timeToStr(answers[i]));
    }
}

TEST_CASE("Table test") {
    Table t(10);
    t.acquire(10);
    t.release(11);
    t.acquire(13);
    t.release(73);
    CHECK(t.getIncome() == 20);
    CHECK(t.getUseTime() == 61);
    CHECK(t.isFree());
    t.acquire(74);
    CHECK(!t.isFree());
    CHECK_THROWS(t.acquire(75));
    CHECK_THROWS(t.release(0));
    t.release(76);
    CHECK_THROWS(t.release(77));
}

TEST_CASE("Person test") {
    Person a(11, "a");
    Person b(12, "a");
    Person c(10, "c");
    CHECK((a < b & b < c));
}

TEST_CASE("Event to string test") {
    int time = 600;
    std::string name = "Max";
    int table = 0;
    std::string results[] = {
        "10:00 1 Max",
        "10:00 2 Max 1",
        "10:00 3 Max",
        "10:00 4 Max",
        "10:00 11 Max",
        "10:00 12 Max 1",
        "10:00 13 Max",
    };
    EventCome evc(time, name);
    EventSit evs(time, name, table);
    EventWait evw(time, name);
    EventGone evg(time, name);
    EventForceGone evfg(time, name);
    EventSitFromQueue evsfq(time, name, table);
    EventError eve(time, name);
    CHECK(evc.to_string() == results[0]);
    CHECK(evs.to_string() == results[1]);
    CHECK(evw.to_string() == results[2]);
    CHECK(evg.to_string() == results[3]);
    CHECK(evfg.to_string() == results[4]);
    CHECK(evsfq.to_string() == results[5]);
    CHECK(eve.to_string() == results[6]);
}

TEST_CASE("Club add person test") {
    Club club(10, 144, 2, 10);
    club.addClient(10, "10");
    club.addClient(20, "20");
    CHECK(club.getEvents()->size() == 0);
    club.addClient(30, "10");
    CHECK(club.getEvents()->size() == 1);
    club.addClient(200, "200");
    CHECK(club.getEvents()->size() == 2);
    club.addClient(0, "0");
    CHECK(club.getEvents()->size() == 3);
}

TEST_CASE("Club sit person test") {
    Club club(10, 144, 2, 10);
    club.addClient(10, "10");
    club.moveClient(11, "10", 0);
    CHECK(club.getEvents()->size() == 0);
    club.addClient(12, "10");
    CHECK(club.getEvents()->size() == 1);
    club.moveClient(13, "12", 2);
    CHECK(club.getEvents()->size() == 2);
    club.moveClient(15, "10", 1);
    CHECK(club.getEvents()->size() == 2);
    club.moveClient(17, "10", 1);
    CHECK(club.getEvents()->size() == 3);
    club.addClient(18, "18");
    CHECK(club.getEvents()->size() == 3);
    club.moveClient(20, "18", 1);
    CHECK(club.getEvents()->size() == 4);
    club.moveClient(20, "18", 0);
    CHECK(club.getEvents()->size() == 4);
}

TEST_CASE("Club drop person test") {
    Club club(10, 144, 2, 10);
    club.addClient(11, "11");
    club.moveClient(12, "11", 0);
    club.dropClient(13, "11");
    club.addClient(21, "11");
    club.moveClient(22, "11", 0);
    club.dropClient(23, "11");
    CHECK(club.getEvents()->size() == 0);
    CHECK(club.getProfit()->at(0).getIncome() == 20);
    club.dropClient(24, "11");
    CHECK(club.getEvents()->size() == 1);
}

TEST_CASE("Club wait person test") {
    Club club(10, 144, 1, 10);
    club.addClient(11, "11");
    club.waitClient(12, "11");
    CHECK(club.getEvents()->size() == 1);
    club.moveClient(13, "11", 0);
    club.addClient(14, "14");
    club.waitClient(15, "14");
    CHECK(club.getEvents()->size() == 1);
    club.waitClient(16, "16");
    CHECK(club.getEvents()->size() == 2);
    club.addClient(17, "17");
    club.addClient(18, "18");
    club.waitClient(19, "17");
    CHECK(club.getEvents()->size() == 2);
    club.waitClient(20, "18");
    CHECK(club.getEvents()->size() == 3);
    club.dropClient(21, "11");
    CHECK(club.getEvents()->size() == 4);
}

TEST_CASE("Club close test") {
    Club club(10, 144, 2, 10);
    club.addClient(11, "11");
    club.moveClient(140, "11", 0);
    club.close();
    CHECK(club.getProfit()->at(0).getIncome() == 10);
    CHECK(club.getProfit()->at(1).getIncome() == 0);
    CHECK(club.getProfit()->at(0).getUseTime() == 4);
    CHECK(club.getProfit()->at(1).getUseTime() == 0);
}

TEST_CASE("Client queue test") {
    ClientQueue q;
    Person one(1, "1");
    Person two(2, "2");
    Person three(3, "3");
    CHECK(!q.in(one));
    q.push(one);
    CHECK(q.in(one));
    Person same_name(2, "1");
    CHECK(!q.in(same_name));
    q.push(two);
    q.push(two);
    CHECK(q.size() == 2);
    q.push(three);
    q.pop(two);
    CHECK(q.popLeft().name == one.name);
    CHECK(q.popLeft().name == three.name);
    CHECK(q.size() == 0);
}

TEST_CASE("ClubLogger test") {
    ClubLogger logger(1, 10, 1, 10);
    EventCome* evc = new EventCome(1, "1");
    EventSit* evs = new EventSit(2, "1", 0);
    EventCome* evc2 = new EventCome(3, "3");
    EventWait* evw = new EventWait(4, "3");
    EventGone* evg = new EventGone(5, "1");
    EventGone* evg2 = new EventGone(6, "3");
    std::vector<IncomeEvent*> events = {evc, evs, evc2, evw, evg, evg2};
    for (auto ev: events) {
        logger.processEvent(ev);
    }
    CHECK(logger.getEvents()->size() == 7);
    CHECK(logger.getProfit()->at(0).getIncome() == 20);
    CHECK(logger.getProfit()->at(0).getUseTime() == 4);
}