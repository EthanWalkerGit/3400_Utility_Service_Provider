#include "databaseManager.h" // include database manager class
#include <iostream>          // for i/o
#include <vector>            // for vector container
#include <sqlite3.h>         // for sqlite3 database operations
#include "provider.h"        // include provider class
#include "UtilityService.h"  // include utility service class
#include "customer.h"        // include customer class
#include "customer_menu.h"   // include customer menu class

using std::cerr;   // use cerr for error output
using std::cout;   // use cout for standard output
using std::endl;   // use endl for new line
using std::string; // use string class

// ************************************************************
//
//  Constructor: DatabaseManager
//
//  Description: initializes database manager
//
// ************************************************************
DatabaseManager::DatabaseManager() : db(nullptr) {}

// ************************************************************
//
//  Destructor: ~DatabaseManager
//
//  Description: closes db connection if open
//
// ************************************************************
DatabaseManager::~DatabaseManager()
{
    closeDatabase(); // ensure the database is closed when the object is destroyed
}

// ************************************************************
//
//  Function: openDatabase
//
//  Description: opens database using the string provided
//
// ************************************************************
bool DatabaseManager::openDatabase(const string &dbName)
{
    int rc = sqlite3_open(dbName.c_str(), &db); // open db
    if (rc != SQLITE_OK)                        // check if open failed
    {
        cerr << "Error opening SQLite database: " << sqlite3_errmsg(db) << endl; // error message
        return false;
    }
    else // open successful
    {
        cout << "Database opened/created successfully!" << endl; // success message
        return true;
    }
}

// ************************************************************
//
//  Function: closeDatabase
//
//  Description: closes database connection
//
// ************************************************************
void DatabaseManager::closeDatabase()
{
    if (db) // ensure db exists and can be closed
    {
        sqlite3_close(db);                             // close db
        db = nullptr;                                  // reset the database handle
        cout << "Database connection closed." << endl; // success message
    }
}

// ************************************************************
//
//  Function: getConnection
//
//  Description: returns database connection
//
// ************************************************************
sqlite3 *DatabaseManager::getConnection()
{
    return db; // return the database connection
}

// ************************************************************
//
//  Function: executeQuery
//
// *ATTENTION* this gets overloaded to handle different params
//
//  Description: executes sql query
//
// ************************************************************
bool DatabaseManager::executeQuery(const string &query) // execute basic query
{
    if (!db) // check if db is open
    {
        cerr << "Database is not open!" << endl; // print error if db is closed
        return false;                            // return false since query can't run
    }

    char *errMsg = nullptr;                                              // pointer for error message
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg); // execute query
    if (rc != SQLITE_OK)                                                 // check if query execution failed
    {
        cerr << "SQL error: " << errMsg << endl; // print error message
        sqlite3_free(errMsg);                    // free error message memory
        return false;                            // return false since query failed
    }

    cout << "Query executed successfully!" << endl; // print success message
    return true;                                    // return true since query succeeded
}

// ************************************************************
//
//  Function: executeQuery
//
// *ATTENTION* this IS overloaded to handle different params
//
//  Description: executes sql query
//
// ************************************************************
bool DatabaseManager::executeQuery(const string &query, vector<Bill> &bills) // execute query, store results in bills
{
    if (!db) // check if db is open
    {
        cerr << "Database is not open!" << endl; // print error if db is closed
        return false;                            // return false since query can't run
    }

    char *errMsg = nullptr;                                                      // pointer for error message
    int rc = sqlite3_exec(db, query.c_str(), callbackFunction, &bills, &errMsg); // execute query, pass bills vector
    if (rc != SQLITE_OK)                                                         // check if query execution failed
    {
        cerr << "SQL error: " << errMsg << endl; // print error message
        sqlite3_free(errMsg);                    // free error message memory
        return false;                            // return false since query failed
    }

    cout << "Query executed successfully!" << endl; // print success message
    return true;                                    // return true since query succeeded
}

// ************************************************************
//
//  Function: executeQuery
//
// *ATTENTION* this IS overloaded to handle different params
//
//  Description: executes sql query
//
// ************************************************************
vector<vector<string>> DatabaseManager::executeQuery(const string &query, bool returnResults) // execute query, return results if needed
{
    vector<vector<string>> results; // store query results

    if (!db) // check if db is open
    {
        cerr << "Database is not open!" << endl; // print error if db is closed
        return results;                          // return empty results
    }

    char *errMsg = nullptr; // pointer for error message
    int rc = sqlite3_exec(db, query.c_str(), [](void *data, int argc, char **argv, char **colNames) -> int
                          {
        vector<vector<string>> *results = static_cast<vector<vector<string>>*>(data); // cast data to results vector
        vector<string> row; // store single row
        for (int i = 0; i < argc; ++i) // loop through columns
        {
            row.push_back(argv[i] ? argv[i] : "NULL"); // add column value or "NULL" if null
        }
        results->push_back(row); // add row to results
        return 0; }, &results, &errMsg); // execute query, store results

    if (rc != SQLITE_OK) // check if query execution failed
    {
        cerr << "SQL error: " << errMsg << endl; // print error message
        sqlite3_free(errMsg);                    // free error message memory
        return {};                               // return empty results on error
    }

    return results; // return query results
}

// ************************************************************
//
//  Function: callbackFunction
//
//  Description: callback function for retrieving bills
//
// ************************************************************
int DatabaseManager::callbackFunction(void *data, int argc, char **argv, char **azColName)
{
    vector<Bill> *bills = static_cast<vector<Bill> *>(data); // cast data to vector<Bill> pointer

    if (argc < 5) // ensure row has at least 5 columns (billID, serviceID, amount, dueDate, status)
        return 1; // return 1 to signal an issue (incomplete data)

    // convert row data from char* to appropriate types
    int billID = stoi(argv[0]);              // convert billID to int
    int serviceID = stoi(argv[1]);           // convert serviceID to int
    double amount = stod(argv[2]);           // convert amount to double
    string dueDate = argv[3] ? argv[3] : ""; // store dueDate (check for null)
    string status = argv[4] ? argv[4] : "";  // store status (check for null)

    bills->emplace_back(billID, 0, serviceID, 1, amount, dueDate, status); // add new Bill object to the vector

    return 0;
}

// ************************************************************
//
//  Function: getLastInsertId
//
//  Description: returns id of last inserted record
//
// ************************************************************
int DatabaseManager::getLastInsertId()
{
    return static_cast<int>(sqlite3_last_insert_rowid(db)); // cast value as an int
}

// ************************************************************
//
//  Function: initTables
//
//  Description: creates necessary tables if they do not exist
//
// ************************************************************
void DatabaseManager::initTables()
{
    const string createCustomers = R"(
        CREATE TABLE IF NOT EXISTS Customers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            address TEXT NOT NULL
        );
    )"; // query to create the Customers table

    const string createProviders = R"(
        CREATE TABLE IF NOT EXISTS providers (
            providerID INTEGER PRIMARY KEY AUTOINCREMENT,
            P_Name TEXT NOT NULL,
            Sales REAL DEFAULT 0.00
        );
    )"; // query to create the Customers table

    const string createServices = R"(
        CREATE TABLE IF NOT EXISTS services (
            serviceID INTEGER PRIMARY KEY AUTOINCREMENT,
            S_Name TEXT NOT NULL,
            rate_per_unit REAL,
            fixed_charge REAL,
            providerID INTEGER,
            FOREIGN KEY(providerID) REFERENCES providers(providerID)
        );
    )"; // query to create the Services table

    executeQuery(createCustomers); // execute the queries to create the tables
    executeQuery(createProviders);
    executeQuery(createServices);
}

// ************************************************************
//
//  Function: resetDatabase
//
//  Description: clears all data and resets database
//
// ************************************************************
void DatabaseManager::resetDatabase()
{
    const string dropCustomers = "DROP TABLE IF EXISTS Customers;"; // query to drop the Customers table
    const string dropProviders = "DROP TABLE IF EXISTS providers;"; // query to drop the Providers table
    const string dropServices = "DROP TABLE IF EXISTS services;";   // query to drop the Services table

    executeQuery(dropCustomers); // execute the queries to drop the tables
    executeQuery(dropProviders);
    executeQuery(dropServices);

    cout << "All tables dropped successfully!" << endl;
}

// ************************************************************
//
//  Function: insertData
//
//  Description: inserts initial data into database
//
// ************************************************************
void DatabaseManager::insertData()
{
    const string insertProviders = R"(
        INSERT INTO providers (P_Name) VALUES
        ('GasPlus'),
        ('EcoHydro'),
        ('FastNet Internet'),
        ('SmartWater'),
        ('UrbanEnergy'),
        ('GreenConnect'),
        ('PowerGrid Inc.'),
        ('BlueFlame Utilities'),
        ('HomeWave Solutions'),
        ('MetroEnergy');
    )"; // query to inset data into the providers table
    const string insertServices = R"(
        INSERT INTO services (S_Name, rate_per_unit, fixed_charge, providerID) VALUES
        ('Natural Gas', 0.19, 24.0, 1),
        ('TV', 0.42, 28.0, 1),
        ('Mobile Phone', 0.11, 35.0, 1),
        ('Home Phone', 0.06, 20.0, 1),
        ('Electric', 0.14, 22.0, 1),
        ('Water', 0.0035, 18.0, 1),
        ('Sewerage', 0.0025, 15.0, 1),
        ('Natural Gas', 0.18, 23.0, 2),
        ('TV', 0.4, 27.0, 2),
        ('Mobile Phone', 0.105, 33.0, 2),
        ('Home Phone', 0.055, 18.0, 2),
        ('Electric', 0.135, 21.0, 2),
        ('Water', 0.0032, 17.0, 2),
        ('Sewerage', 0.0022, 14.0, 2),
        ('Natural Gas', 0.2, 25.0, 3),
        ('TV', 0.43, 30.0, 3),
        ('Mobile Phone', 0.12, 36.0, 3),
        ('Home Phone', 0.058, 21.0, 3),
        ('Electric', 0.145, 23.0, 3),
        ('Water', 0.0036, 19.0, 3),
        ('Sewerage', 0.0024, 16.0, 3);
    )"; // query to inset data into the services table

    executeQuery(insertProviders); // execute the queries to insert data
    executeQuery(insertServices);

    cout << "Data inserted successfully!" << endl;
}

// ************************************************************
//
//  Function: LoadData
//
//  Description: loads providers, services, and customers from db
//
// ************************************************************
void DatabaseManager::LoadData(vector<provider> &providers, vector<UtilityService> &services, vector<Customer> &customers)
{
    sqlite3 *db = getConnection(); // get the db connection

    const char *sql_p = "SELECT providerID, P_Name , Sales FROM providers;";                                 // query providers
    const char *sql_s = "SELECT serviceID, S_Name, rate_per_unit, fixed_charge , providerID FROM services;"; // query services
    const char *sql_b = "SELECT BillID, CustomerID, ServiceID, Amount, DueDate, Status FROM bills;";         // query bills

    sqlite3_stmt *stmt_p; // sql statement pointer for providers
    sqlite3_stmt *stmt_s; // sql statement pointer for services
    sqlite3_stmt *stmt_b; // sql statement pointer for bills

    if (sqlite3_prepare_v2(db, sql_p, -1, &stmt_p, nullptr) != SQLITE_OK) // prepare provider query
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }
    if (sqlite3_prepare_v2(db, sql_s, -1, &stmt_s, nullptr) != SQLITE_OK) // prepare service query
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }
    if (sqlite3_prepare_v2(db, sql_b, -1, &stmt_b, nullptr) != SQLITE_OK) // prepare bill query
    {
        cerr << "Failed to prepare bills statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    while (sqlite3_step(stmt_p) == SQLITE_ROW) // process provider data
    {
        int pid = sqlite3_column_int(stmt_p, 0);                                                     // get provider id
        string p_name = reinterpret_cast<const char *>(sqlite3_column_text(stmt_p, 1));              // get provider name
        double sales = sqlite3_column_double(stmt_s, 2);                                             // get sales amount
        providers.emplace_back(pid, p_name, sales);                                                  // store provider data
        cout << "Loaded provider: ID=" << pid << ", Name=" << p_name << ", Sales=" << sales << endl; // debug print
    }
    while (sqlite3_step(stmt_s) == SQLITE_ROW) // process service data
    {
        int sid = sqlite3_column_int(stmt_s, 0);                                        // get service id
        string s_name = reinterpret_cast<const char *>(sqlite3_column_text(stmt_s, 1)); // get service name
        double rpu = sqlite3_column_double(stmt_s, 2);                                  // get rate per unit
        double fc = sqlite3_column_double(stmt_s, 3);                                   // get fixed charge
        int pid = sqlite3_column_int(stmt_s, 4);                                        // get provider id
        services.emplace_back(sid, s_name, rpu, fc, pid);                               // store service data

        cout << "Loaded service: ID=" << sid << ", Name=" << s_name << ", Rate=" << rpu << ", Fixed Charge=" << fc << ", ProviderID=" << pid << endl; // debug print
    }
    while (sqlite3_step(stmt_b) == SQLITE_ROW) // process bill data
    {
        int billID = sqlite3_column_int(stmt_b, 0);                                      // get bill id
        int customerID = sqlite3_column_int(stmt_b, 1);                                  // get customer id
        int serviceID = sqlite3_column_int(stmt_b, 2);                                   // get service id
        double amount = sqlite3_column_double(stmt_b, 3);                                // get amount
        string dueDate = reinterpret_cast<const char *>(sqlite3_column_text(stmt_b, 4)); // get due date
        string status = reinterpret_cast<const char *>(sqlite3_column_text(stmt_b, 5));  // get status

        for (auto &customer : customers) // find customer and add bill
        {
            if (customer.getCustomerID() == customerID)
            {
                customer.addBill(Bill(billID, customerID, serviceID, 1, amount, dueDate, status)); // add bill
                break;
            }
        }
    }

    sqlite3_finalize(stmt_p); // free provider statement
    sqlite3_finalize(stmt_s); // free service statement
    sqlite3_finalize(stmt_b); // free bill statement

    const char *sql2 = "SELECT customer_id, customer_name, address FROM Customers;"; // query customers
    sqlite3_stmt *stmt2;                                                             // sql statement pointer for customers

    if (sqlite3_prepare_v2(db, sql2, -1, &stmt2, nullptr) != SQLITE_OK) // prepare customer query
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return; // no need to close db, managed by DatabaseManager
    }

    while (sqlite3_step(stmt2) == SQLITE_ROW) // process customer data
    {
        int id = sqlite3_column_int(stmt2, 0);                                                        // get customer id
        string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt2, 1));                  // get customer name
        string address = reinterpret_cast<const char *>(sqlite3_column_text(stmt2, 2));               // get address
        cout << "Loaded customer: ID=" << id << ", Name=" << name << ", Address=" << address << endl; // debug print
        customers.emplace_back(id, name, address);                                                    // store customer data
    }

    sqlite3_finalize(stmt2); // free customer statement
}

int DatabaseManager::getNextBillID()
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT MAX(BillID) FROM bills;"; // query max bill id

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) // prepare query
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return -1; // return -1 if query fails
    }

    int nextBillID = 1;                   // default to 1 if no bills exist
    if (sqlite3_step(stmt) == SQLITE_ROW) // check result row
    {
        int maxBillID = sqlite3_column_int(stmt, 0); // get max bill id
        if (maxBillID != SQLITE_NULL)                // check if valid
        {
            nextBillID = maxBillID + 1; // increment bill id
        }
    }

    sqlite3_finalize(stmt); // free statement
    return nextBillID;      // return next bill id
}
