#include "DatabaseManager.h"
#include <iostream>
#include <vector>
#include <sqlite3.h>
#include "provider.h"       // Include your provider header
#include "UtilityService.h" // Include your UtilityService header

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

// Execute a SQL query
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
    else
    {
        cout << "Query executed successfully!" << endl;
        return true;
    }
}

// Method to get the last inserted row ID
int DatabaseManager::getLastInsertId()
{
    return static_cast<int>(sqlite3_last_insert_rowid(db));
}

// Initialize tables in the database
void DatabaseManager::initTables()
{
    const string createCustomers = R"(
        CREATE TABLE IF NOT EXISTS Customers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            address TEXT NOT NULL
        );
    )";

    executeQuery(createCustomers);
}

// Load data into providers and services
void DatabaseManager::LoadData(std::vector<provider> &providers, std::vector<UtilityService> &services)
{
    sqlite3 *db = getConnection(); // Get the database connection

    const char *sql = "SELECT providers.providerID, providers.P_Name, services.serviceID, services.S_Name, services.rate_per_unit, services.fixed_charge FROM providers JOIN services ON providers.providerID = services.providerID;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return; // No need to close db here, as it is managed by DatabaseManager
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int pid = sqlite3_column_int(stmt, 0);
        string p_name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        int sid = sqlite3_column_int(stmt, 2);
        string s_name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        double rpu = sqlite3_column_double(stmt, 4);
        double fc = sqlite3_column_double(stmt, 5);
        providers.emplace_back(pid, p_name);
        services.emplace_back(sid, s_name, rpu, fc, pid);
    }

    sqlite3_finalize(stmt); // Finalize the statement
}
