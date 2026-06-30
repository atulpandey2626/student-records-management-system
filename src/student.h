#ifndef STUDENT_H
#define STUDENT_H

#include "database.h"
#include <string>

class StudentManager {
private:
    Database& db;
public:
    StudentManager(Database& database) : db(database) {}
    
    void addStudent();
    void viewAllStudents();
    void searchStudent();
    void updateStudent();
    void deleteStudent();
    void viewResults();
};

#endif
