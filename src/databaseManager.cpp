#include "databaseManager.h"
#include <iostream>
#include <vector>
#include <sqlite3.h>
#include "provider.h"
#include "UtilityService.h"
#include "customer.h"
#include "customer_menu.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;

// Constructor
DatabaseManager::DatabaseManager() : db(nullptr) {}

// Destructor
DatabaseManager::~DatabaseManager()
{
    closeDatabase(); // Ensure the database is closed when the object is destroyed
}

// Open or create a database
bool DatabaseManager::openDatabase(const string &dbName)
{
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Error opening SQLite database: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    else
    {
        cout << "Database opened/created successfully!" << endl;
        return true;
    }
}

// Close the database
void DatabaseManager::closeDatabase()
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr; // Reset the database handle
        cout << "Database connection closed." << endl;
    }
}

// Method to get the database connection
sqlite3 *DatabaseManager::getConnection()
{
    return db; // Return the database connection
}

// Original executeQuery (unchanged)
bool DatabaseManager::executeQuery(const string &query)
{
    if (!db)
    {
        cerr << "Database is not open!" << endl;
        return false;
    }

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }

    cout << "Query executed successfully!" << endl;
    return true;
}

// Overloaded executeQuery with bills parameter
bool DatabaseManager::executeQuery(const string &query, vector<Bill> &bills)
{
    if (!db)
    {
        cerr << "Database is not open!" << endl;
        return false;
    }

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), callbackFunction, &bills, &errMsg); // Pass bills vector
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }

    cout << "Query executed successfully!" << endl;
    return true;
}

// Define the callback function that fills the vector with results
int DatabaseManager::callbackFunction(void *data, int argc, char **argv, char **azColName)
{
    vector<Bill> *bills = static_cast<vector<Bill> *>(data); // Cast to vector<Bill> pointer

    if (argc < 5) // Ensure we have enough columns
        return 1; // Abort if data is incomplete

    int billID = stoi(argv[0]);
    int serviceID = stoi(argv[1]);
    double amount = stod(argv[2]);
    string dueDate = argv[3] ? argv[3] : "";
    string status = argv[4] ? argv[4] : "";

    // Assuming Bill constructor: Bill(int billID, int customerID, int serviceID, int providerID, double amount, string dueDate, string status)
    bills->emplace_back(billID, 0, serviceID, 1, amount, dueDate, status);

    return 0; // Success
}

// Method to get the last inserted row ID
int DatabaseManager::getLastInsertId()
{
    return static_cast<int>(sqlite3_last_insert_rowid(db));
}

void DatabaseManager::initTables()
{
    // Query to create the Customers table
    const string createCustomers = R"(
        CREATE TABLE IF NOT EXISTS Customers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            address TEXT NOT NULL
        );
    )";

    // Query to create the Providers table
    const string createProviders = R"(
        CREATE TABLE IF NOT EXISTS providers (
            providerID INTEGER PRIMARY KEY AUTOINCREMENT,
            P_Name TEXT NOT NULL
        );
    )";

    // Query to create the Services table
    const string createServices = R"(
        CREATE TABLE IF NOT EXISTS services (
            serviceID INTEGER PRIMARY KEY AUTOINCREMENT,
            S_Name TEXT NOT NULL,
            rate_per_unit REAL,
            fixed_charge REAL,
            providerID INTEGER,
            FOREIGN KEY(providerID) REFERENCES providers(providerID)
        );
    )";

    // Execute the queries to create the tables
    executeQuery(createCustomers);
    executeQuery(createProviders);
    executeQuery(createServices);
}

void DatabaseManager::resetDatabase()
{
    // Query to drop the Customers table
    const string dropCustomers = "DROP TABLE IF EXISTS Customers;";

    // Query to drop the Providers table
    const string dropProviders = "DROP TABLE IF EXISTS providers;";

    // Query to drop the Services table
    const string dropServices = "DROP TABLE IF EXISTS services;";

    // Execute the queries to drop the tables
    executeQuery(dropCustomers);
    executeQuery(dropProviders);
    executeQuery(dropServices);

    cout << "All tables dropped successfully!" << endl;
}

void DatabaseManager::insertData()
{
    // Insert data into the providers table
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
    )";

    // Insert data into the services table
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
    )";

    // Execute the queries to insert data
    executeQuery(insertProviders);
    executeQuery(insertServices);

    cout << "Data inserted successfully!" << endl;
}

// Load data into providers and services
void DatabaseManager::LoadData(vector<provider> &providers, vector<UtilityService> &services, vector<Customer> &customers)
{
    sqlite3 *db = getConnection(); // Get the database connection

    const char *sql_p = "SELECT providerID, P_Name FROM providers;";
    const char *sql_s = "SELECT serviceID, S_Name, rate_per_unit, fixed_charge , providerID FROM services;";
    const char *sql_b = "SELECT BillID, CustomerID, ServiceID, Amount, DueDate, Status FROM bills;";
    sqlite3_stmt *stmt_p;
    sqlite3_stmt *stmt_s;
    sqlite3_stmt *stmt_b;

    if (sqlite3_prepare_v2(db, sql_p, -1, &stmt_p, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }
    if (sqlite3_prepare_v2(db, sql_s, -1, &stmt_s, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return;
    }
    if (sqlite3_prepare_v2(db, sql_b, -1, &stmt_b, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare bills statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    while (sqlite3_step(stmt_p) == SQLITE_ROW)
    {
        int pid = sqlite3_column_int(stmt_p, 0);
        string p_name = reinterpret_cast<const char *>(sqlite3_column_text(stmt_p, 1));

        providers.emplace_back(pid, p_name);
    }
    while (sqlite3_step(stmt_s) == SQLITE_ROW)
    {

        int sid = sqlite3_column_int(stmt_s, 0);
        string s_name = reinterpret_cast<const char *>(sqlite3_column_text(stmt_s, 1));
        double rpu = sqlite3_column_double(stmt_s, 2);
        double fc = sqlite3_column_double(stmt_s, 3);
        int pid = sqlite3_column_int(stmt_s, 4);
        services.emplace_back(sid, s_name, rpu, fc, pid);
    }
    while (sqlite3_step(stmt_b) == SQLITE_ROW)
    {
        int billID = sqlite3_column_int(stmt_b, 0);
        int customerID = sqlite3_column_int(stmt_b, 1);
        int serviceID = sqlite3_column_int(stmt_b, 2);
        double amount = sqlite3_column_double(stmt_b, 3);
        string dueDate = reinterpret_cast<const char *>(sqlite3_column_text(stmt_b, 4));
        string status = reinterpret_cast<const char *>(sqlite3_column_text(stmt_b, 5));

        // Add the bill to the appropriate customer
        for (auto &customer : customers)
        {
            if (customer.getCustomerID() == customerID)
            {
                customer.addBill(Bill(billID, customerID, serviceID, 1, amount, dueDate, status)); // Replace '1' with correct providerID if needed
                break;
            }
        }
    }

    sqlite3_finalize(stmt_p);
    sqlite3_finalize(stmt_s);
    sqlite3_finalize(stmt_b);

    const char *sql2 = "SELECT customer_id, customer_name, address FROM Customers;";
    sqlite3_stmt *stmt2;

    if (sqlite3_prepare_v2(db, sql2, -1, &stmt2, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return; // No need to close db here, as it is managed by DatabaseManager
    }

    while (sqlite3_step(stmt2) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt2, 0);
        string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt2, 1));
        string address = reinterpret_cast<const char *>(sqlite3_column_text(stmt2, 2));
        cout << "Loaded customer: ID=" << id << ", Name=" << name << ", Address=" << address << endl; // Debug line
        customers.emplace_back(id, name, address);
    }

    sqlite3_finalize(stmt2); // Finalize the statement
}

int DatabaseManager::getNextBillID()
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT MAX(BillID) FROM bills;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return -1; // Error retrieving Bill ID
    }

    int nextBillID = 1; // Default if no Bill IDs exist (first BillID)
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int maxBillID = sqlite3_column_int(stmt, 0);
        if (maxBillID != SQLITE_NULL)
        {
            nextBillID = maxBillID + 1;
        }
    }

    sqlite3_finalize(stmt); // Finalize the statement
    return nextBillID;
}
