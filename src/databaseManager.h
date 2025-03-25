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
#include "customer_menu.h"
#include "bill.h"

class Customer;

using namespace std;

class DatabaseManager
{
private:
    sqlite3 *db;

    // Callback function for retrieving bills
    static int callbackFunction(void *data, int argc, char **argv, char **colNames);

public:
    DatabaseManager();
    ~DatabaseManager();

    // opens database using the string provided
    bool openDatabase(const std::string &dbName);
    // closes database connection
    void closeDatabase();
    // Overloaded versions of executeQuery
    bool executeQuery(const string &query);                      // Original version
    bool executeQuery(const string &query, vector<Bill> &bills); // New version
    int getLastInsertId();
    int getNextBillID();
    void initTables();
    void resetDatabase();
    void insertData();
    sqlite3 *getConnection();
    void LoadData(vector<provider> &providers, vector<UtilityService> &services, vector<Customer> &customers);
};

#endif