#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

extern "C"
{
#include "sqlite3.h"
}
#include <iostream>
#include <string>
#include <vector>
#include "UtilityService.h"
#include "provider.h"

using namespace std;

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
    void resetDatabase();
    void insertData();
    sqlite3 *getConnection();
    void LoadData(vector<provider> &providers, vector<UtilityService> &services);
};

#endif