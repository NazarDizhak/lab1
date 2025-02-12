// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <fstream>
#include "programs/program1.hpp"
#include "programs/program2.hpp"
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


uint64_t sum_nums(const std::vector<unsigned>& data) {
    uint64_t sum = 0;
    for (unsigned num : data) {
        sum += num;
    }
    return sum%64;
}

int main(int argc, char* argv[]) {
  	try{
    	if (argc != 3) {
        	throw INVALID_ARGS;
    	}

    	std::string input_file = argv[1];
    	int method = std::stoi(argv[2]);

    	std::vector<unsigned> result;

    	std::ifstream file(input_file);
    	if (!file.is_open()) {
        	throw FILE_OPEN_ERROR;
    	}

        std::vector<std::string> data = readFileIdiom(input_file);

    	auto start = std::chrono::high_resolution_clock::now();

    	switch (method) {
        	case 1:
            	result = uv_ss(data);
        		break;
        	case 2:
            	result = uv_ato(data);
        		break;
        	case 3:
            	result = uv_stod(data);
        		break;
        	case 4:
            	result = uv_from_chars(data);
        		break;
        	case 5:
            	result = uv_sscanf(data);
        		break;
        	default:
                throw INVALID_METHOD;
    	}

    	auto end = std::chrono::high_resolution_clock::now();
    	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  		std::cout << duration << std::endl;

    	std::cout << sum_nums(result) << std::endl;
	} catch (const CustomError& e) {
          std::cout << e.what() << " (Error code: " << e.code() << ")" << std::endl;
	} catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return 64;
    }
    return SUCCESS;
}
