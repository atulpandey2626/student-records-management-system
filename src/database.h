#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database {
private:
    sqlite3* db;
public:
    Database(const std::string& dbPath);
    ~Database();
    sqlite3* getHandle() const;
    bool executeQuery(const std::string& sql);
    void initializeSchema();
};

#endif
