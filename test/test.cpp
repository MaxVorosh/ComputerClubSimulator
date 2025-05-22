#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "parser.h"
#include "timeConvertion.h"

#include <vector>
#include <iostream>

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

TEST_CASE("Parser number validator test") {
    Parser parser;
    std::string goodNumbers[] = {"42", "-017"};
    std::string badNumbers[] = {"0x2A", "3.1459", "1 one", "-19-1"};
    for (int i = 0; i < 2; ++i) {
        CHECK(parser.checkDecimal(goodNumbers[i]));
    }
    for (int i = 0; i < 4; ++i) {
        CHECK(!parser.checkDecimal(badNumbers[i]));
    }
}

TEST_CASE("Parser name validator test") {
    Parser parser;
    std::string goodNames[] = {"max", "many-separators_in_1-name"};
    std::string badNames[] = {"john doe", "Capital", "apostroph's", "иван"};
    for (int i = 0; i < 2; ++i) {
        CHECK(parser.checkName(goodNames[i]));
    }
    for (int i = 0; i < 4; ++i) {
        CHECK(!parser.checkName(badNames[i]));
    }
}

TEST_CASE("Parser test") {
    Parser parser;
    SUBCASE("Base test") {
        std::string filename = "./../examples/base_example.txt";
        std::vector<std::string> result = {
            "09:00", "08:48 1 client1", "08:48 13 NotOpenYet", "09:41 1 client1", "09:48 1 client2",
            "09:52 3 client1", "09:52 13 ICanWaitNoLonger!", "09:54 2 client1 1", "10:25 2 client2 2",
            "10:58 1 client3", "10:59 2 client3 3", "11:30 1 client4", "11:35 2 client4 2",
            "11:35 13 PlaceIsBusy", "11:45 3 client4", "12:33 4 client1", "12:33 12 client4 1",
            "12:43 4 client2", "15:52 4 client4", "19:00 11 client3", "19:00", "1 70 05:58", "2 30 02:18", 
            "3 90 08:01"
        };
        std::vector<std::string> out;
        parser.parse(filename, out);
        REQUIRE(out.size() == result.size());
        for (int i = 0; i < out.size(); ++i) {
            CHECK(out[i] == result[i]);
        }
    }

    SUBCASE("Bad test") {
        std::string filename = "./../examples/bad_example.txt";
        std::vector<std::string> result = {"09:48 5 client1 1"};
        std::vector<std::string> out;
        parser.parse(filename, out);
        REQUIRE(out.size() == result.size());
        for (int i = 0; i < out.size(); ++i) {
            CHECK(out[i] == result[i]);
        }
    }

    SUBCASE("Long queue") {
        std::string filename = "./../examples/long_queue.txt";
        std::vector<std::string> result = {
            "09:00",
            "10:00 1 client1",
            "10:01 1 client2",
            "10:02 1 client3",
            "10:03 1 client4",
            "10:04 1 client5",
            "10:05 1 client6",
            "10:06 1 client7",
            "10:07 1 client8",
            "10:08 1 client9",
            "10:09 1 client10",
            "10:10 1 client11",
            "10:11 1 client12",
            "10:12 1 client13",
            "10:13 1 client14",
            "10:14 1 client15",
            "10:15 1 client16",
            "10:16 1 client17",
            "10:17 1 client18",
            "10:18 1 client19",
            "10:19 1 client20",
            "10:20 2 client1 1",
            "10:21 2 client2 2",
            "10:22 2 client3 3",
            "10:23 2 client4 4",
            "10:24 2 client5 5",
            "10:25 2 client6 6",
            "10:26 2 client7 7",
            "10:27 2 client8 8",
            "10:28 2 client9 9",
            "10:29 2 client10 10",
            "10:30 3 client11",
            "10:31 3 client12",
            "10:32 3 client13",
            "10:33 3 client14",
            "10:34 3 client15",
            "10:35 3 client16",
            "10:36 3 client17",
            "10:37 3 client18",
            "10:38 3 client19",
            "10:39 3 client20",
            "10:40 4 client1",
            "10:40 12 client11 1",
            "10:41 4 client2",
            "10:41 12 client12 2",
            "10:42 4 client3",
            "10:42 12 client13 3",
            "10:43 4 client4",
            "10:43 12 client14 4",
            "10:44 4 client5",
            "10:44 12 client15 5",
            "10:45 4 client6",
            "10:45 12 client16 6",
            "10:46 4 client7",
            "10:46 12 client17 7",
            "10:47 4 client8",
            "10:47 12 client18 8",
            "10:48 4 client9",
            "10:48 12 client19 9",
            "10:49 4 client10",
            "10:49 12 client20 10",
            "10:50 4 client11",
            "10:51 4 client12",
            "10:52 4 client13",
            "10:53 4 client14",
            "10:54 4 client15",
            "10:55 4 client16",
            "10:56 4 client17",
            "10:57 4 client18",
            "10:58 4 client19",
            "10:59 4 client20",
            "19:00",
            "1 20 00:30",
            "2 20 00:30",
            "3 20 00:30",
            "4 20 00:30",
            "5 20 00:30",
            "6 20 00:30",
            "7 20 00:30",
            "8 20 00:30",
            "9 20 00:30",
            "10 20 00:30"
        };
        std::vector<std::string> out;
        parser.parse(filename, out);
        REQUIRE(out.size() == result.size());
        for (int i = 0; i < out.size(); ++i) {
            CHECK(out[i] == result[i]);
        }
    }
    SUBCASE("wrong parameters cnt") {
        std::string filename = "./../examples/wrong_parameters_cnt.txt";
        std::vector<std::string> result = {"08:48 1"};
        std::vector<std::string> out;
        parser.parse(filename, out);
        REQUIRE(out.size() == result.size());
        for (int i = 0; i < out.size(); ++i) {
            CHECK(out[i] == result[i]);
        }
    }

    SUBCASE("Force gone everyone") {
        std::string filename = "./../examples/force_gone_all_example.txt";
        std::vector<std::string> result = {"09:00", "09:00 1 client1", "09:01 1 client2", "09:02 1 client3",
            "09:03 1 client4", "09:04 1 client5", "09:05 2 client1 1", "09:06 2 client2 2", "09:07 2 client3 3",
            "09:08 2 client4 4", "09:09 2 client5 5", "09:10 1 client6", "09:11 1 client7", "09:12 1 client8",
            "09:13 1 client9", "09:14 1 client10", "09:15 3 client6", "09:16 3 client7", "09:17 3 client8",
            "09:18 3 client9", "09:19 3 client10", "09:20 1 client11", "09:21 1 client12", "09:22 1 client13",
            "09:23 1 client14", "09:24 1 client15", "12:00 11 client1", "12:00 11 client10", "12:00 11 client11",
            "12:00 11 client12", "12:00 11 client13", "12:00 11 client14", "12:00 11 client15",
            "12:00 11 client2", "12:00 11 client3", "12:00 11 client4", "12:00 11 client5", "12:00 11 client6",
            "12:00 11 client7", "12:00 11 client8", "12:00 11 client9", "12:00", "1 3 02:55", "2 3 02:54",
            "3 3 02:53", "4 3 02:52", "5 3 02:51"
        };
        std::vector<std::string> out;
        parser.parse(filename, out);
        REQUIRE(out.size() == result.size());
        for (int i = 0; i < out.size(); ++i) {
            CHECK(out[i] == result[i]);
        }
    }

    SUBCASE("Invalid tables") {
        std::string filenames[] = {"./../examples/bad_tables/letters.txt", "./../examples/bad_tables/mix.txt",
             "./../examples/bad_tables/negative.txt", "./../examples/bad_tables/two_values.txt",
              "./../examples/bad_tables/zero.txt"
        };
        std::vector<std::string> results = {"one", "11tables", "-12", "3 5", "0"};
        for (int i = 0; i < 5; ++i) {
            std::vector<std::string> out;
            parser.parse(filenames[i], out);
            REQUIRE(out.size() == 1);
            CHECK(out[0] == results[i]);
        }
    }

    SUBCASE("Invalid cost") {
        std::string filenames[] = {"./../examples/bad_cost/letters.txt", "./../examples/bad_cost/mix.txt",
             "./../examples/bad_cost/negative.txt", "./../examples/bad_cost/two_values.txt",
              "./../examples/bad_cost/zero.txt"
        };
        std::vector<std::string> results = {"one", "11tables", "-12", "3 5", "0"};
        for (int i = 0; i < results.size(); ++i) {
            std::vector<std::string> out;
            parser.parse(filenames[i], out);
            REQUIRE(out.size() == 1);
            CHECK(out[0] == results[i]);
        }
    }

    SUBCASE("Invalid name") {
        std::string filenames[] = {"./../examples/bad_names/capital.txt", "./../examples/bad_names/cyrillic.txt",
            "./../examples/bad_names/star.txt", "./../examples/bad_names/two_values.txt",
       };
       std::vector<std::string> results = {"12:00 2 Capital 1", "12:00 3 иван", "12:00 1 regexp*", "12:00 4 john doe"};
       for (int i = 0; i < results.size(); ++i) {
           std::vector<std::string> out;
           parser.parse(filenames[i], out);
           REQUIRE(out.size() == 1);
           CHECK(out[0] == results[i]);
       }
    }

    SUBCASE("Invalid event") {
        std::string filenames[] = {"./../examples/bad_event/bad_time.txt", "./../examples/bad_event/big_table.txt",
            "./../examples/bad_event/big_type.txt", "./../examples/bad_event/negative_table.txt",
            "./../examples/bad_event/negative_type.txt", "./../examples/bad_event/zero_table.txt",
            "./../examples/bad_event/zero_type.txt"
       };
       std::vector<std::string> results = {"9:35 1 client1", "09:36 2 client1 2", "09:35 11 client1",
            "09:36 2 client1 -1", "09:35 -1 client1", "09:36 2 client1 0", "09:35 0 client1"
        };
       for (int i = 0; i < results.size(); ++i) {
           std::vector<std::string> out;
           parser.parse(filenames[i], out);
           REQUIRE(out.size() == 1);
           CHECK(out[0] == results[i]);
       }
    }

    SUBCASE("Invalid format") {
        std::string filenames[] = {"./../examples/bad_format/little_args_1.txt",
            "./../examples/bad_format/little_args_2.txt", "./../examples/bad_format/little_args_3.txt",
            "./../examples/bad_format/little_args_4.txt", "./../examples/bad_format/many_args_1.txt",
            "./../examples/bad_format/many_args_2.txt", "./../examples/bad_format/many_args_3.txt",
            "./../examples/bad_format/one_time.txt", "./../examples/bad_format/swap_time.txt"
       };
       std::vector<std::string> results = {"12:30 1", "12:30 2 client1", "3 client1", "4",
         "12:30 1 client1 smth", "12:30 2 client1 1 12", "12:30 3 client1 12", "12:00", "12:29 1 client2"
        };
       for (int i = 0; i < results.size(); ++i) {
           std::vector<std::string> out;
           parser.parse(filenames[i], out);
           REQUIRE(out.size() == 1);
           CHECK(out[0] == results[i]);
       }
    }

    SUBCASE("Invalid values") {
        std::string filenames[] = {"./../examples/bad_values/header_time.txt",
            "./../examples/bad_values/swap_header_time.txt", "./../examples/bad_values/table.txt",
            "./../examples/bad_values/three_time_header.txt", "./../examples/bad_values/time.txt",
            "./../examples/bad_values/type.txt"
       };
       std::vector<std::string> results = {"12:00 thirteen", "13:00 12:00", "12:30 2 client1 table", 
         "12:00 13:00 14:00", "time 1 client1", "12:30 one client1"
        };
       for (int i = 0; i < results.size(); ++i) {
           std::vector<std::string> out;
           parser.parse(filenames[i], out);
           REQUIRE(out.size() == 1);
           CHECK(out[0] == results[i]);
       }
    }
}