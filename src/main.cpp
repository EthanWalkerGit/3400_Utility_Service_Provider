#include "customer.h"

using namespace std;

// ************************************************************
//
//  Function: main
//
//  Description: Runs program
//
// ************************************************************
int main()
{
    DatabaseManager dbManager;

    // Open the database
    if (!dbManager.openDatabase("utilityproviders.db"))
    {
        return 1; // Exit if the database couldn't be opened
    }

    // initialize tables in database if not done so already
    dbManager.initTables();

    // Initialize customers directly
    Customer customer1(dbManager, "Alice Johnson", "123 Maple St");
    Customer customer2(dbManager, "Bob Smith", "456 Oak Ave");
    Customer customer3(dbManager, "Charlie Brown", "789 Pine Rd");

    std::vector<Customer> customers = {customer1, customer2, customer3};

    Customer *currentCustomer = nullptr; // pointer to logged-in customer

    int choice; // variable to hold user input options

    while (true) // infinite loop to repeat until user log in or exits
    {
        cout << "\n--- Utility Billing System ---\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; // recieve input

        if (choice == 1) // 1: proceed to login
        {
            int id;
            cout << "\nEnter Customer ID: ";                  // prompt for a id of an existing customer
            cin >> id;                                        // recieve input
            currentCustomer = Customer::login(customers, id); // use customer login function
        }
        else if (choice == 2) // 2: proceed to registration
        {
            string name, address;
            int id = customers.size() + 1; // assign a new id
            cout << "\nEnter Name: ";      // prompt for name
            cin.ignore();
            getline(cin, name);                                                        // recieve input
            cout << "\nEnter Address: ";                                               // prompt for address
            getline(cin, address);                                                     // recieve input
            currentCustomer = Customer::registerAccount(customers, id, name, address); // use customer register function
        }
        else if (choice == 3) // 3: exit
        {
            cout << "\nExiting...\n";
            break; // exit loop
        }
        else // otherwise: get input again
        {
            cout << "\nInvalid choice! Try again.\n";
        }

        if (currentCustomer) // check if logged in
        {
            break; // proceed to main menu after login
        }
    }

    if (!currentCustomer) // check if not legged in
    {
        return 0; // exit if user didn't log in
    }

    while (true) // infinite loop to keep displaying user options until they exit
    {
        cout << "\n--- Utility Billing System ---\n";
        cout << "1. Subscribe to a service\n";
        cout << "2. View bills\n";
        cout << "3. Make a payment\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; // take input

        switch (choice)
        {
        case 1:
            currentCustomer->subscribeService();
            break;
        case 2:
            currentCustomer->viewBill();
            break;
        case 3:
            int billID;
            cout << "Enter Bill ID to pay: ";
            cin >> billID;
            currentCustomer->makePayment(billID);
            break;
        case 4:
            cout << "Logging out...\n";
            currentCustomer = nullptr;
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

        if (!currentCustomer)
        {
            break; // Return to login menu
        }
    }

    dbManager.closeDatabase();

    return 0;
}
