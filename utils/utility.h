#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include <iostream>
#include <limits>
#include <algorithm>
#include <regex>

using namespace std;

// Global counter
int globalNasabahCounter = 1;

string generateIdNasabah() {
    stringstream ss;
    ss << "NSB" << setw(3) << setfill('0') << globalNasabahCounter++;
    return ss.str();
}
string generateNoRekening() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(10000000, 99999999);
    return to_string(dis(gen));
}

bool isBlank(const std::string& str) {
    return std::all_of(str.begin(), str.end(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c));
    });
}

std::string getSafeLine(const std::string& prompt) {
    std::string input;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flush input
            std::cout << "Input tidak valid. Silahkan coba lagi\n";
            continue;
        }

        if (input.empty() || isBlank(input)) {
            std::cout << "Input tidak valid. Silahkan coba lagi\n";
            continue;
        }

        return input;
    }
}

bool isValidDateFormat(const std::string& date) {
    // Match exactly 2 digits - 2 digits - 4 digits
    std::regex pattern(R"(^\d{2}-\d{2}-\d{4}$)");
    if (!std::regex_match(date, pattern)) {
        return false;
    }

    // Parse and check range
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    // Optional: Check for days per month
    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    // Leap year check
    bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (month == 2 && leap) {
        if (day > 29) return false;
    } else {
        if (day > daysInMonth[month - 1]) return false;
    }

    return true;
}