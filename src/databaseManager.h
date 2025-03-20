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
#include "customer.h"

using namespace std;

class DatabaseManager
{
private:
    sqlite3 *db;

public:
    DatabaseManager();
    ~DatabaseManager();

    // opens database using the string provided
    bool openDatabase(const std::string &dbName);
    // closes database connection
    void closeDatabase();
    // executes SQL query string passed to the function
    bool executeQuery(const std::string &query);
    int getLastInsertId();
    void initTables();
    void resetDatabase();
    void insertData();
    sqlite3 *getConnection();
    void LoadData(vector<provider> &providers, vector<UtilityService> &services, vector<Customer> &customers);
};

#endif