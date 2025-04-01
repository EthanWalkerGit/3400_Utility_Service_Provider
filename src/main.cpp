#include <iostream>          // for i/o
#include <vector>            // for vector conatiner
#include "customer_menu.h"   // include customer_menu class
#include "provider_menu.h"   // include provider_menu class
#include "databaseManager.h" // include db manager class

using namespace std; // use standard namespace

// ************************************************************
//
//  Function: main
//
//  Description: runs program
//
// ************************************************************
int main()
{
    DatabaseManager dbManager; // create db manager object

    if (!dbManager.openDatabase("utilityproviders.db")) // ensure no error when opening database
    {
        return 1; // open failed
    }

    vector<provider> providers;      // vector for providers
    vector<UtilityService> services; // vector for services
    vector<Customer> customers;      // vector for customers

    dbManager.LoadData(providers, services, customers); // call load data to populate vectors

    while (true) // iterate until user exits
    {
        cout << "\n--- Utility Billing System ---\n"; // header
        cout << "1. Login as Customer\n";             // login as customer option
        cout << "2. Login as Provider\n";             // login as provider option
        cout << "3. Register as Customer\n";          // reg as customer option
        cout << "4. Register as Provider\n";          //  reg as provider option
        cout << "5. Exit\n";                          // exit option
        cout << "Enter your choice: ";                // prompt for option

        int choice;    // var for user input choice
        cin >> choice; // get choice

        if (cin.fail()) // if the user enters invalid input (non-integer)
        {
            cin.clear();                                         // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input! Please enter a number.\n";
            continue; // skip the rest of the loop and prompt for input again
        }

        if (choice == 1) // customer Login
        {
            customer_menu(customers, services, providers, dbManager); // fork and go to the customer menu
        }
        else if (choice == 2) // provider Login
        {
            provider_menu(providers, services, dbManager); // fork and go to the provider menu
        }
        else if (choice == 3) // register customer
        {
            string name, address;          // vars for customer info
            int id = customers.size() + 1; // increase size of customer vector
            cout << "\nEnter Name: ";      // prompt for name
            cin.ignore();                  // ignore unwanted parts of input
            getline(cin, name);            // get input
            cout << "Enter Address: ";     // prompt for address
            getline(cin, address);         // get address

            Customer::registerAccount(customers, id, name, address, dbManager); // create new customer using constructor
        }
        else if (choice == 4) // register provider
        {
            add_provider(providers, dbManager); // call add provider function in provider class
        }
        else if (choice == 5) // exit
        {
            cout << "Exiting...\n";
            break; // exit loop
        }
        else // invalid input repreat loop
        {
            cout << "Invalid choice! Try again.\n";
        }
    }

    dbManager.closeDatabase(); // close db
    return 0;
}
