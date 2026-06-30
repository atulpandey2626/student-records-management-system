#include "database.h"
#include <iostream>

Database::Database(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

sqlite3* Database::getHandle() const {
    return db;
}

bool Database::executeQuery(const std::string& sql) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL Error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

void Database::initializeSchema() {
    std::string studentTable = "CREATE TABLE IF NOT EXISTS students (student_id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, course TEXT NOT NULL, year INTEGER NOT NULL, email TEXT UNIQUE NOT NULL, cgpa REAL CHECK(cgpa >= 0 AND cgpa <= 10), created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";
    std::string resultsTable = "CREATE TABLE IF NOT EXISTS results (result_id INTEGER PRIMARY KEY AUTOINCREMENT, student_id INTEGER REFERENCES students(student_id) ON DELETE CASCADE, subject TEXT NOT NULL, marks INTEGER NOT NULL, grade TEXT NOT NULL);";
    
    executeQuery(studentTable);
    executeQuery(resultsTable);
}
