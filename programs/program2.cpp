//
// Created by f1rset on 2/10/25.
//

#include "program2.hpp"

std::vector<unsigned> uv_ss(const std::vector<std::string>& input_data){
    std::vector<unsigned> output_data;
    for (const auto& str : input_data) {
        std::stringstream ss(str);
        unsigned num;
        ss >> num;
        output_data.emplace_back(num);
    }
    return output_data;
}

std::vector<unsigned> uv_ato(const std::vector<std::string>& input_data){
    std::vector<unsigned> output_data;
    for (const auto& str : input_data){
        u_int64_t num = atoi(str.c_str());
        output_data.emplace_back(num);
    }
    return output_data;
}
std::vector<unsigned> uv_stod(const std::vector<std::string>& input_data){
    std::vector<unsigned> output_data;
    for (const auto& str : input_data){
        u_int64_t num = std::stod(str);
        output_data.emplace_back(num);
    }
    return output_data;
}
std::vector<unsigned> uv_from_chars(const std::vector<std::string>& input_data){
    std::vector<unsigned> output_data;
    for (const auto& str : input_data){
        u_int64_t num;
        std::from_chars(str.data(), str.data() + str.size(), num);
        output_data.emplace_back(num);
    }
    return output_data;
}

std::vector<unsigned> uv_sscanf(const std::vector<std::string>& input_data){
    std::vector<unsigned> output_data;
    for (const auto& str : input_data) {
        u_int64_t num;
        sscanf(str.c_str(), "%ld", &num);
        output_data.emplace_back(num);
    }
    u_int64_t sum = 0;
    for (auto nu : output_data){
        sum = sum + nu;
    }
    return output_data;
}