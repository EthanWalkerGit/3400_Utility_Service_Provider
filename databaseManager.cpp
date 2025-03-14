#include "databaseManager.h"
using std::cerr;
using std::cout;
using std::endl;
using std::string;

// Constructor
DatabaseManager::DatabaseManager() : db(nullptr)
{
}

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