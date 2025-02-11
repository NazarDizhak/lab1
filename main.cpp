// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
//#include "options_parser.h"
#include <vector>
#include <string>
#include "programs/program1.hpp"

int main(int argc, char* argv[]) {
//    command_line_options_t command_line_options{argc, argv};
//    std::cout << "A flag value: " << command_line_options.get_A_flag() << std::endl;
    std::vector<std::string> data;
    data = readFileIdiom("data/test.txt");
    std::cout << data.size() << std::endl;
    return 0;
}
