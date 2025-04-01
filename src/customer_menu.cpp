#include "customer_menu.h"   // include customer menu header
#include "customer.h"        // include customer class
#include "databaseManager.h" // include database manager class
#include "provider_menu.h"   // include provider menu header

// ************************************************************
//
//  Function: viewservices
//
//  Description: displays services filtered by provider id
//
// ************************************************************
void viewservices(std::vector<UtilityService> &services, int providerID)
{
    bool found = false; // flag to check if any service is found

    for (const auto &service : services) // iterate over services
    {
        if (providerID == -1 || service.getPID() == providerID) // if no provider is selected show all services
        {
            cout << "Service ID: " << service.getSID() // display service information
                 << " | Name: " << service.getName()
                 << " | Rate: " << service.getRate()
                 << " | Fixed Cost: " << service.getFC() << endl;
            found = true; // mark as found
        }
    }
    if (!found) // check if no service was found
    {
        cout << "No services available for this provider.\n"; // print message if no services found
    }
}

// ************************************************************
//
//  Function: customer_menu
//
//  Description: handles the customer menu interaction
//
// ************************************************************
void customer_menu(vector<Customer> &customers, vector<UtilityService> &services, vector<provider> &providers, DatabaseManager &dbManager)
{
    int customerID;                // variable to store customer id
    cout << "Enter Customer ID: "; // prompt for customer id
    cin >> customerID;             // recive user input

    if (cin.fail()) // check for invalid input
    {
        cin.clear();                                                  // clear error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n');          // discard invalid input
        cout << "Invalid input! Please enter a valid Customer ID.\n"; // print error message
        return;                                                       // return to menu
    }

    Customer *customer = Customer::login(customers, customerID); // attempt login
    if (!customer)
    {
        cout << "Invalid ID! Returning to main menu.\n"; // print error message
        return;                                          // return to menu
    }

    customer->loadBillsFromDatabase(dbManager); // load bills from database
    int choice;                                 // store users menu choice

    while (true) // loop to iterate until user exits
    {
        cout << "\n--- Customer Menu ---\n"; // print menu header
        cout << "1. Search for service\n";   // option to search for service
        cout << "2. View bills\n";           // option to view bills
        cout << "3. Make a payment\n";       // option to make payment
        cout << "4. Logout\n";               // option to logout
        cout << "Enter your choice: ";       // prompt for menu choice

        cin >> choice; // recive users choice input

        if (cin.fail()) // check for invalid input
        {
            cin.clear();                                         // clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input! Please enter a number.\n";   // print error message
            continue;                                            // ask for input again
        }

        switch (choice) // switch statement to handle the differnt option cases
        {
        case 1: // search
        {
            int providerChoice;                           // variable for provider choice
            cout << "\n--- Available Providers ---\n";    // print provider header
            for (size_t i = 0; i < providers.size(); ++i) // iterate over amount of providers
            {
                cout << i + 1 << ". " << providers[i].getName() << endl; // print provider names
            }
            cout << providers.size() + 1 << ". Exit\n";              // exit option
            cout << "Select a provider (or choose Exit to leave): "; // prompt for provider selection
            cin >> providerChoice;                                   // get user input for provider options

            if (cin.fail()) // check for invalid input
            {
                cin.clear();                                             // clear error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');     // discard invalid input
                cout << "Invalid input! Please enter a valid number.\n"; // print error message
                continue;                                                // ask for input again
            }

            if (providerChoice == providers.size() + 1) // exit option is the last so check if user enteres 1+ last option
            {
                cout << "Exiting service search.\n"; // print exit message
                break;                               // exit service search process
            }

            if (providerChoice < 1 || providerChoice > providers.size()) // check for invalid range integers
            {
                cout << "Invalid choice. Try again.\n"; // print error message
                continue;                               // allow user to retry
            }

            int providerID = providerChoice - 1; // convert to 0-based index
            int serviceID;                       // variable for service id

            cout << "\n--- " << providers[providerID].getName() << "'s Available Services ---\n"; // print provider services header
            viewservices(services, providerID);                                                   // display available services

            while (true) // loop to iterate until user exits
            {
                cout << "Enter the Service ID to subscribe to (0 to go back): "; // prompt for service id
                cin >> serviceID;                                                // recive user input for a service id

                if (cin.fail()) // check for invalid input
                {
                    cin.clear();                                             // clear error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');     // discard invalid input
                    cout << "Invalid input! Please enter a valid number.\n"; // print error message
                    continue;                                                // ask for input again
                }

                if (serviceID == 0) // go back to provider list
                {
                    break; // exit this loop and go back to provider list loop
                }

                bool validService = false;           // flag for valid service
                for (const auto &service : services) // iterate over services to see if 1 matches the users input
                {
                    if (service.getSID() == serviceID && service.getPID() == providerID) // check if entered service id is valid
                    {
                        validService = true; // mark as valid
                        break;               // return to previous loop
                    }
                }

                if (validService) // if service exists
                {
                    customer->subscribeToService(dbManager, services, providers, providerID, serviceID); // proceed to subscribe to service
                    break;                                                                               // exit after subscription
                }
                else // not valid
                {
                    cout << "Invalid Service ID. Please try again.\n"; // print error message
                }
            }
            break; // exit provider selection
        }
        case 2:                               // view bills
            customer->viewBill();             // view bill details function call
            break;                            // exit view case
        case 3:                               // make payment
            int billID;                       // variable for bill id
            cout << "Enter Bill ID to pay: "; // prompt for bill id
            cin >> billID;                    // recive user input into bill id

            if (cin.fail()) // check for invalid input
            {
                cin.clear();                                              // clear error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');      // discard invalid input
                cout << "Invalid input! Please enter a valid Bill ID.\n"; // print error message
                continue;                                                 // ask for input again
            }

            customer->makePayment(billID, dbManager); // call make payment function with biill id so it can be identified
            break;                                    // exit payment case
        case 4:                                       // logout
            cout << "Logging out...\n";               // print logout message
            return;                                   // return to main menu
        default:                                      // if none of the main 4
            cout << "Invalid choice. Try again.\n";   // print error message
        }
    }
}