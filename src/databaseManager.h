#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

extern "C"
{
#include "sqlite3.h"
}
#include <iostream>
#include <string>

class DatabaseManager
{
private:
    sqlite3 *db;

public:
    DatabaseManager();
    ~DatabaseManager();

    bool openDatabase(const std::string &dbName);
    void closeDatabase();
    bool executeQuery(const std::string &query);
    int getLastInsertId();
    void initTables();
};

#endif