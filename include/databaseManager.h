#ifndef DATABASEMANAGER_H // prevent multiple inclusions
#define DATABASEMANAGER_H // define header guard

extern "C"
{
#include "sqlite3.h" // include sqlite3 for database handling
}

#include <iostream>         // for i/o
#include <string>           // for strings
#include <vector>           // for vector container
#include "UtilityService.h" // include utility service class
#include "provider.h"       // include provider class
#include "customer.h"       // include customer class
#include "customer_menu.h"  // include customer menu class
#include "bill.h"           // include bill class

class Customer; // forward declaration of customer class

using namespace std; // use standard namespace

// ************************************************************
//
//  Class: DatabaseManager
//
//  Description: handle db operations
//
// ************************************************************
class DatabaseManager
{
private:
    sqlite3 *db; // pointer to db

    // ************************************************************
    //
    //  Function: callbackFunction
    //
    //  Description: callback function for retrieving bills
    //
    // ************************************************************
    static int callbackFunction(void *data, int argc, char **argv, char **colNames);

public:
    // ************************************************************
    //
    //  Constructor: DatabaseManager
    //
    //  Description: initializes database manager
    //
    // ************************************************************
    DatabaseManager();

    // ************************************************************
    //
    //  Destructor: ~DatabaseManager
    //
    //  Description: closes db connection if open
    //
    // ************************************************************
    ~DatabaseManager();

    // ************************************************************
    //
    //  Function: openDatabase
    //
    //  Description: opens database using the string provided
    //
    // ************************************************************
    bool openDatabase(const std::string &dbName);

    // ************************************************************
    //
    //  Function: closeDatabase
    //
    //  Description: closes database connection
    //
    // ************************************************************
    void closeDatabase();

    // ************************************************************
    //
    //  Function: executeQuery (overloaded)
    //
    //  Description: executes sql query
    //
    // ************************************************************
    bool executeQuery(const string &query);
    bool executeQuery(const string &query, vector<Bill> &bills);
    vector<vector<string>> executeQuery(const string &query, bool returnResults);

    // ************************************************************
    //
    //  Function: getLastInsertId
    //
    //  Description: returns id of last inserted record
    //
    // ************************************************************
    int getLastInsertId();

    // ************************************************************
    //
    //  Function: getNextBillID
    //
    //  Description: retrieves next available bill id
    //
    // ************************************************************
    int getNextBillID();

    // ************************************************************
    //
    //  Function: initTables
    //
    //  Description: creates necessary tables if they do not exist
    //
    // ************************************************************
    void initTables();

    // ************************************************************
    //
    //  Function: resetDatabase
    //
    //  Description: clears all data and resets database
    //
    // ************************************************************
    void resetDatabase();

    // ************************************************************
    //
    //  Function: insertData
    //
    //  Description: inserts initial data into database
    //
    // ************************************************************
    void insertData();

    // ************************************************************
    //
    //  Function: getConnection
    //
    //  Description: returns database connection
    //
    // ************************************************************
    sqlite3 *getConnection();

    // ************************************************************
    //
    //  Function: LoadData
    //
    //  Description: loads providers, services, and customers from db
    //
    // ************************************************************
    void LoadData(vector<provider> &providers, vector<UtilityService> &services, vector<Customer> &customers);
};

#endif