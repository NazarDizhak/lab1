// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <fstream>
#include "programs/program1.hpp"
#include <chrono>
#include <cstdint>
#include <exception>

class CustomError : public std::exception {
public:
    CustomError(const std::string& message, int code)
        : msg(message), err_code(code) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }

    int code() const noexcept {
        return err_code;
    }

private:
    std::string msg;
    int err_code;
};

#define SUCCESS 0
#define INVALID_ARGS CustomError("Неправильна кількість аргументів", 1)
#define INVALID_METHOD CustomError("Неправильний номер методу", 2)
#define FILE_OPEN_ERROR CustomError("Не вдалося відкрити файл з вхідними даними", 3)
#define OUTPUT_FILE_ERROR 4
#define INPUT_READ_ERROR 5
#define OUTPUT_WRITE_ERROR 6


uint64_t letters_count(const std::vector<std::string>& data) {
    uint64_t count = 0;
    for (const auto& str : data) {
        count += str.length();
    }
    return count;
}

int main(int argc, char* argv[]) {
  	try{
    	if (argc != 3) {
        	throw INVALID_ARGS;
    	}

    	std::string input_file = argv[1];
    	int method = std::stoi(argv[2]);
    	std::vector<std::string> data;

    	std::ifstream file(input_file);
    	if (!file.is_open()) {
        	throw FILE_OPEN_ERROR;
    	}

    	auto start = std::chrono::high_resolution_clock::now();

    	switch (method) {
        	case 1:
            	data = readFileIdiom(input_file);
        		break;
        	case 2:
            	data = readFileFull(input_file);
        		break;
        	case 3:
            	data = readFileFullStr(input_file);
        		break;
        	case 4:
            	data = readFileFullRLF(input_file);
        		break;
        	case 5:
            	data = readBadIdea1(input_file);
        		break;
        	default:
                throw INVALID_METHOD;
    	}

    	auto end = std::chrono::high_resolution_clock::now();
    	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    	std::cout << duration << std::endl;
    	std::cout << letters_count(data) << std::endl;
	} catch (const CustomError& e) {
          std::cout << e.what() << " (Error code: " << e.code() << ")" << std::endl;

	} catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return 64;
    }
    return SUCCESS;
}
