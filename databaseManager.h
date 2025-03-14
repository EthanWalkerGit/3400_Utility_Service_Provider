#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <sqlite3.h>
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
};

#endif