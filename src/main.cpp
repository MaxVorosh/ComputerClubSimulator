#include <iostream>
#include "parser.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: ./ClubSim <filename>" << std::endl;
        return 0;
    }
    Parser parser;
    std::vector<std::string> lines;
    std::string filename(argv[1]);
    parser.parse(filename, lines);
    for (int i = 0; i < lines.size(); ++i) {
        std::cout << lines[i] << std::endl;
    }
}