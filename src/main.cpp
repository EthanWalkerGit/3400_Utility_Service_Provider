#include <iostream>
#include <vector>
#include "customer_menu.h"
#include "provider_menu.h"
#include "databaseManager.h"

using namespace std;

int main()
{
    DatabaseManager dbManager;

    if (!dbManager.openDatabase("utilityproviders.db"))
    {
        return 1;
    }

    vector<provider> providers;
    vector<UtilityService> services;
    vector<Customer> customers;

    dbManager.LoadData(providers, services, customers);

    while (true)
    {
        cout << "\n--- Utility Billing System ---\n";
        cout << "1. Login as Customer\n";
        cout << "2. Login as Provider\n";
        cout << "3. Register as Customer\n";
        cout << "4. Register as Provider\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (cin.fail()) // If the user enters invalid input (non-integer)
        {
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter a number.\n";
            continue; // Skip the rest of the loop and prompt for input again
        }

        if (choice == 1) // Customer Login
        {
            customer_menu(customers, services, providers, dbManager);
        }
        else if (choice == 2) // Provider Login
        {
            provider_menu(providers, services, dbManager);
        }
        else if (choice == 3) // Register Customer
        {
            string name, address;
            int id = customers.size() + 1;
            cout << "\nEnter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Address: ";
            getline(cin, address);
            Customer::registerAccount(customers, id, name, address, dbManager);
        }
        else if (choice == 4) // Register Provider
        {
            add_provider(providers, dbManager);
        }
        else if (choice == 5) // Exit
        {
            cout << "Exiting...\n";
            break;
        }
        else
        {
            cout << "Invalid choice! Try again.\n";
        }
    }

    dbManager.closeDatabase();
    return 0;
}
