#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

class Validation {
public:
    static bool isValidEmail(const std::string& email);
    static bool isValidCGPA(double cgpa);
    static bool isValidYear(int year);
    static std::string trim(const std::string& str);
};

#endif
