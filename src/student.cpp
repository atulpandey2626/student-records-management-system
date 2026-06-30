#include "student.h"
#include "validation.h"
#include <iostream>
#include <iomanip>

void StudentManager::addStudent() {
    std::string name, course, email;
    int year;
    double cgpa;

    std::cout << "\n=== Add New Student ===\n";
    std::cin.ignore();
    std::cout << "Enter Name: "; std::getline(std::cin, name);
    std::cout << "Enter Course: "; std::getline(std::cin, course);
    
    std::cout << "Enter Year: "; std::cin >> year;
    if (!Validation::isValidYear(year)) {
        std::cout << "Invalid Year! Must be between 1 and 5.\n"; return;
    }

    std::cout << "Enter Email: "; std::cin >> email;
    if (!Validation::isValidEmail(email)) {
        std::cout << "Invalid Email Format!\n"; return;
    }

    std::cout << "Enter CGPA: "; std::cin >> cgpa;
    if (!Validation::isValidCGPA(cgpa)) {
        std::cout << "Invalid CGPA! Must be between 0.0 and 10.0.\n"; return;
    }

    std::string query = "INSERT INTO students (name, course, year, email, cgpa) VALUES ('" 
                        + name + "', '" + course + "', " + std::to_string(year) + ", '" + email + "', " + std::to_string(cgpa) + ");";

    if (db.executeQuery(query)) {
        sqlite3_int64 lastId = sqlite3_last_insert_rowid(db.getHandle());
        std::cout << "Student added successfully!\n";
        std::cout << "ID: " << lastId << "\n";
    } else {
        std::cout << "Failed to add student. Email might already exist.\n";
    }
}

void StudentManager::viewAllStudents() {
    std::string query = "SELECT * FROM students;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db.getHandle(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "Failed to fetch data.\n";
        return;
    }

    std::cout << "\n" << std::left << std::setw(8) << "ID" << std::setw(20) << "Name" << std::setw(15) << "Course" 
              << std::setw(8) << "Year" << std::setw(25) << "Email" << std::setw(6) << "CGPA" << "\n";
    std::cout << std::string(82, '-') << "\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << std::left << std::setw(8) << sqlite3_column_int(stmt, 0)
                  << std::setw(20) << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))
                  << std::setw(15) << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))
                  << std::setw(8) << sqlite3_column_int(stmt, 3)
                  << std::setw(25) << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4))
                  << std::setw(6) << sqlite3_column_double(stmt, 5) << "\n";
    }
    sqlite3_finalize(stmt);
}

void StudentManager::searchStudent() {
    std::cin.ignore();
    std::cout << "\nEnter Search Keyword (ID, Name, or Course): ";
    std::string keyword;
    std::getline(std::cin, keyword);

    std::string query = "SELECT * FROM students WHERE student_id = '" + keyword + "' OR name LIKE '%" + keyword + "%' OR course LIKE '%" + keyword + "%';";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db.getHandle(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "Query execution error.\n";
        return;
    }

    std::cout << "\nSearch Results:\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << "ID: " << sqlite3_column_int(stmt, 0) 
                  << " | Name: " << sqlite3_column_text(stmt, 1)
                  << " | Course: " << sqlite3_column_text(stmt, 2)
                  << " | Year: " << sqlite3_column_int(stmt, 3)
                  << " | Email: " << sqlite3_column_text(stmt, 4)
                  << " | CGPA: " << sqlite3_column_double(stmt, 5) << "\n";
    }
    sqlite3_finalize(stmt);
}

void StudentManager::updateStudent() {
    int id;
    std::cout << "\nEnter Student ID to Update: ";
    std::cin >> id;

    std::string newCourse, newCgpaStr;
    std::cin.ignore();
    std::cout << "Enter New Course (Leave blank to keep unchanged): ";
    std::getline(std::cin, newCourse);
    std::cout << "Enter New CGPA (Leave blank to keep unchanged): ";
    std::getline(std::cin, newCgpaStr);

    std::string updateFields = "";
    if (!newCourse.empty()) updateFields += "course = '" + newCourse + "'";
    if (!newCgpaStr.empty()) {
        if (!updateFields.empty()) updateFields += ", ";
        updateFields += "cgpa = " + newCgpaStr;
    }

    if (updateFields.empty()) {
        std::cout << "No changes made.\n";
        return;
    }

    std::string query = "UPDATE students SET " + updateFields + " WHERE student_id = " + std::to_string(id) + ";";
    if (db.executeQuery(query)) {
        std::cout << "Student record updated successfully!\n";
    }
}

void StudentManager::deleteStudent() {
    int id;
    std::cout << "\nEnter Student ID to Delete: ";
    std::cin >> id;

    std::string query = "DELETE FROM students WHERE student_id = " + std::to_string(id) + ";";
    if (db.executeQuery(query)) {
        std::cout << "Student record deleted safely.\n";
    }
}

void StudentManager::viewResults() {
    int id;
    std::cout << "\nEnter Student ID to view Academic Performance: ";
    std::cin >> id;

    std::string query = "SELECT subject, marks, grade FROM results WHERE student_id = " + std::to_string(id) + ";";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db.getHandle(), query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "Failed to fetch results.\n";
        return;
    }

    std::cout << "\n--- Academic Report Card ---\n";
    std::cout << std::left << std::setw(20) << "Subject" << std::setw(10) << "Marks" << std::setw(6) << "Grade" << "\n";
    std::cout << std::string(36, '-') << "\n";

    bool found = false;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        found = true;
        std::cout << std::left << std::setw(20) << sqlite3_column_text(stmt, 0)
                  << std::setw(10) << sqlite3_column_int(stmt, 1)
                  << std::setw(6) << sqlite3_column_text(stmt, 2) << "\n";
    }
    if (!found) std::cout << "No graded records found for Student ID " << id << ".\n";
    sqlite3_finalize(stmt);
}
