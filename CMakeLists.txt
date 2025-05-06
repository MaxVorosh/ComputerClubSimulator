cmake_minimum_required(VERSION 3.0)
project(ComputerClubSimulator)

cmake_policy(SET CMP0072 NEW)
cmake_policy(SET CMP0074 NEW)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

add_executable(ClubSim
    ./src/main.cpp
    ./include/clientQueue.h
    ./include/club.h
    ./include/clubLogger.h
    ./include/event.h
    ./include/incomeEvent.h
    ./include/parser.h
    ./include/person.h
    ./include/table.h
    ./include/timeConvertion.h
    ./src/clientQueue.cpp
    ./src/club.cpp
    ./src/clubLogger.cpp
    ./src/event.cpp
    ./src/incomeEvent.cpp
    ./src/parser.cpp
    ./src/person.cpp
    ./src/table.cpp
    ./src/timeConvertion.cpp
)

target_include_directories(ClubSim PUBLIC ./include)

add_executable(ClubSimTest
    ./test/test.cpp
    ./include/clientQueue.h
    ./include/club.h
    ./include/clubLogger.h
    ./include/event.h
    ./include/incomeEvent.h
    ./include/parser.h
    ./include/person.h
    ./include/table.h
    ./include/timeConvertion.h
    ./src/clientQueue.cpp
    ./src/club.cpp
    ./src/clubLogger.cpp
    ./src/event.cpp
    ./src/incomeEvent.cpp
    ./src/parser.cpp
    ./src/person.cpp
    ./src/table.cpp
    ./src/timeConvertion.cpp
)

target_include_directories(ClubSimTest PUBLIC ./include)

add_test(NAME ClubSimTest COMMAND ClubSimTest)