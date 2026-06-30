#include "validation.h"
#include <regex>

bool Validation::isValidEmail(const std::string& email) {
    const std::regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.\w+)+)");
    return std::regex_match(email, pattern);
}

bool Validation::isValidCGPA(double cgpa) {
    return cgpa >= 0.0 && cgpa <= 10.0;
}

bool Validation::isValidYear(int year) {
    return year >= 1 && year <= 5;
}

std::string Validation::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (std::string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}
