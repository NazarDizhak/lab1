//
// Created by f1rset on 2/10/25.
//

#ifndef LAB1_PRODUCTIVITY__STETSIUK_CHUPA__PROGRAM2_H
#define LAB1_PRODUCTIVITY__STETSIUK_CHUPA__PROGRAM2_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <charconv>

std::vector<unsigned> uv_ss(const std::vector<std::string>& input_data);
std::vector<unsigned> uv_ato(const std::vector<std::string>& input_data);
std::vector<unsigned> uv_stod(const std::vector<std::string>& input_data);
std::vector<unsigned> uv_from_chars(const std::vector<std::string>& input_data);
std::vector<unsigned> uv_sscanf(const std::vector<std::string>& input_data);

#endif //LAB1_PRODUCTIVITY__STETSIUK_CHUPA__PROGRAM2_H
