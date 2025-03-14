#include "databaseManager.h"

int main()
{
    DatabaseManager dbManager;

    // Open the database
    if (!dbManager.openDatabase("utilityproviders.db"))
    {
        return 1; // Exit if the database couldn't be opened
    }

    // Create a table
    const std::string createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS Customers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            email TEXT NOT NULL
        );
    )";

    if (!dbManager.executeQuery(createTableQuery))
    {
        return 1; // Exit if the query failed
    }

    // Close the database
    dbManager.closeDatabase();

    return 0;
}