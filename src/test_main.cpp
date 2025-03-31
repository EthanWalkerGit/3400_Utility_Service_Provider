#include "customer.h"
#include "UtilityService.h"
#include "provider.h"
#include "databaseManager.h"

using namespace std;

void print_services(string servicename, vector<UtilityService> &services)
{
    cout << "id --- Service Name --- Rate --- Fixed charge" << endl;
    for (const auto &s : services)
    {
        if (s.getName() == servicename)
        {
            cout << s.getSID() << " ----- " << s.getName() << " ----- " << s.getRate() << " ----- " << s.getFC() << endl;
        }
    }
};

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
    //  dbManager.initTables();

    vector<provider> providers;
    vector<UtilityService> services;
    vector<Customer> customers;

    dbManager.LoadData(providers, services, customers);

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
            getline(cin, name);                                                                   // recieve input
            cout << "\nEnter Address: ";                                                          // prompt for address
            getline(cin, address);                                                                // recieve input
            currentCustomer = Customer::registerAccount(customers, id, name, address, dbManager); // use customer register function
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
        dbManager.closeDatabase();
        return 0; // exit if user didn't log in
    }

    while (true) // infinite loop to keep displaying user options until they exit
    {
        cout << "\n--- Utility Billing System ---\n";
        cout << "1. View services\n";
        cout << "2. Subscribe to a service\n";
        cout << "3. View bills\n";
        cout << "4. Make a payment\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; // take input

        switch (choice)
        {
        case 1:
        {
            int opp;
            cout << "\n---Select a Service Category---\n";
            cout << "1. Natural Gas\n";
            cout << "2. Internet Service\n";
            cout << "3. Hydro\n";
            cout << "Enter Option: ";
            cin >> opp;

            if (opp == 1)
            {
                print_services("Natural Gas", services);
            }
            else if (opp == 2)
            {
                opp = 0;
                cout << "\n1. TV\n";
                cout << "2. Mobile Phone\n";
                cout << "3. Home Phone\n";
                cout << "Enter Option: ";

                cin >> opp;
                if (opp == 1)
                {
                    print_services("TV", services);
                }
                else if (opp == 2)
                {
                    print_services("Mobile Phone", services);
                }
                else if (opp == 3)
                {
                    print_services("Home Phone", services);
                }
            }
            else if (opp == 3)
            {
                opp = 0;
                cout << "\n1. Electric\n";
                cout << "2. Water\n";
                cout << "3. Sewerage\n";
                cout << "Enter Option: ";

                cin >> opp;
                if (opp == 1)
                {
                    print_services("Electric", services);
                }
                else if (opp == 2)
                {
                    print_services("Water", services);
                }
                else if (opp == 3)
                {
                    print_services("Sewerage", services);
                }
            }
        }
        break;

        case 2:
            // currentCustomer->subscribeToService();
            break;
        case 3:
            currentCustomer->viewBill();
            break;
        case 4:
        {
            int billID;
            cout << "Enter Bill ID to pay: ";
            cin >> billID;
            // currentCustomer->makePayment(billID);
            cout << billID;
        }
        break;
        case 5:
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