//
// Created by f1rset on 2/10/25.
//

#include <limits>
#include "program1.hpp"

std::vector<std::string> readFileIdiom(const std::string& file_path){

    std::ifstream file(file_path);
    std::vector<std::string> data;
    std::string word;
//    if (!file){
//        throw Error();
//    }

    while (file >> word){
        data.emplace_back(word);
    }

    return data;
}

std::vector<std::string> readFileFull(const std::string& file_path){
    std::vector<std::string> data;
    std::stringstream ss;
    std::fstream file(file_path);

    ss << file.rdbuf();
    std::string word;

    while (ss >> word){
        data.emplace_back(word);
    }
    return data;
}

std::vector<std::string> readFileFullStr(const std::string& file_path){
    std::vector<std::string> data;
    std::stringstream ss;
    std::fstream file(file_path);

    ss << file.rdbuf();
    std::string string = ss.str();
    size_t pos = 0;
    while (pos < string.length()){
        size_t new_pos = string.find_first_of(" \t\n\r", pos);
        if (new_pos == std::string::npos){
            data.emplace_back(string.substr(pos));
            break;
        }
        else{
            data.emplace_back(string.substr(pos, new_pos-pos));
            pos = new_pos+1;
        }
    }
    return data;
}

std::vector<std::string> readFileFullRLF(const std::string& file_path) {
    std::fstream in(file_path);
    std::vector<std::string> data;
    auto const start_pos = in.tellg();
    in.ignore(std::numeric_limits<std::streamsize>::max());
    auto const char_count = in.gcount();
    in.seekg(start_pos);
    auto str = std::string(char_count, char{});
// or std::vector<char>(char_count);
// or you can use unsigned char or signed char
    in.read(&str[0], str.size());
    size_t pos = 0;
    while (pos < str.length()){
        size_t new_pos = str.find_first_of(" \t\n\r", pos);
        if (new_pos == std::string::npos){
            data.emplace_back(str.substr(pos));
            break;
        }
        data.emplace_back(str.substr(pos, new_pos-pos));
        pos = new_pos+1;
    }
//    data.emplace_back(str);
    return data;
}

std::vector<std::string> readBadIdea1 (const std::string& file_path){
    std::fstream file(file_path);
    std::vector<std::string> data;
    auto string = std::string{};
    string.assign(std::istreambuf_iterator<char>{file},
             std::istreambuf_iterator<char>{});
    size_t pos = 0;
    while (pos < string.length()){
        size_t new_pos = string.find_first_of(" \t\n\r", pos);
        if (new_pos == std::string::npos){
            data.emplace_back(string.substr(pos));
            break;
        }
        else{
            data.emplace_back(string.substr(pos, new_pos-pos));
            pos = new_pos+1;
        }
    }
    return data;
}
