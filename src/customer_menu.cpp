#include "customer_menu.h"
#include "customer.h"
#include "databaseManager.h"
#include "provider_menu.h"

void viewservices(std::vector<UtilityService> &services, int providerID)
{
    bool found = false;

    for (const auto &service : services)
    {
        // If no provider is selected (-1), show all services.
        // Otherwise, filter by providerID.
        if (providerID == -1 || service.getPID() == providerID)
        {
            cout << "Service ID: " << service.getSID()
                 << " | Name: " << service.getName()
                 << " | Rate: " << service.getRate()
                 << " | Fixed Cost: " << service.getFC() << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No services available for this provider.\n";
    }
}

void customer_menu(vector<Customer> &customers, vector<UtilityService> &services, vector<provider> &providers, DatabaseManager &dbManager)
{
    int customerID;
    cout << "Enter Customer ID: ";
    cin >> customerID;

    if (cin.fail()) // Check for invalid input
    {
        cin.clear();                                         // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid input! Please enter a valid Customer ID.\n";
        return; // Return to the main menu
    }

    Customer *customer = Customer::login(customers, customerID);
    if (!customer)
    {
        cout << "Invalid ID! Returning to main menu.\n";
        return;
    }

    customer->loadBillsFromDatabase(dbManager);
    int choice;

    while (true)
    {
        cout << "\n--- Customer Menu ---\n";
        cout << "1. Search for service\n";
        cout << "2. View bills\n";
        cout << "3. Make a payment\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail()) // Check for invalid input
        {
            cin.clear();                                         // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter a number.\n";
            continue; // Ask for input again
        }

        switch (choice)
        {
        case 1:
        {
            int providerChoice;
            cout << "\n--- Available Providers ---\n";
            for (size_t i = 0; i < providers.size(); ++i)
            {
                cout << i + 1 << ". " << providers[i].getName() << endl;
            }
            cout << providers.size() + 1 << ". Exit\n";
            cout << "Select a provider (or choose Exit to leave): ";
            cin >> providerChoice;

            if (cin.fail()) // Check for invalid input
            {
                cin.clear();                                         // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input! Please enter a valid number.\n";
                continue; // Ask for input again
            }

            if (providerChoice == providers.size() + 1)
            {
                cout << "Exiting service search.\n";
                break; // Exit the service search process
            }

            if (providerChoice < 1 || providerChoice > providers.size())
            {
                cout << "Invalid choice. Try again.\n";
                continue;
            }

            int providerID = providerChoice - 1; // 0-based index
            int serviceID;

            cout << "\n--- " << providers[providerID].getName() << "'s Available Services ---\n";
            viewservices(services, providerID); // Display available services

            while (true)
            {
                cout << "Enter the Service ID to subscribe to (0 to go back): ";
                cin >> serviceID;

                if (cin.fail()) // Check for invalid input
                {
                    cin.clear();                                         // Clear the error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "Invalid input! Please enter a valid number.\n";
                    continue; // Ask for input again
                }

                if (serviceID == 0) // Go back to providers list
                {
                    break;
                }

                // Check if the entered Service ID is valid
                bool validService = false;
                for (const auto &service : services)
                {
                    if (service.getSID() == serviceID && service.getPID() == providerID)
                    {
                        validService = true;
                        break;
                    }
                }

                if (validService)
                {
                    // Proceed to subscribe to the service
                    customer->subscribeToService(dbManager, services, providers, providerID, serviceID);
                    break; // Exit after subscription
                }
                else
                {
                    cout << "Invalid Service ID. Please try again.\n";
                }
            }
            break; // Exit after provider selection
        }
        case 2:
            customer->viewBill();
            break;
        case 3:
            int billID;
            cout << "Enter Bill ID to pay: ";
            cin >> billID;

            if (cin.fail()) // Check for invalid input
            {
                cin.clear();                                         // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input! Please enter a valid Bill ID.\n";
                continue; // Ask for input again
            }

            customer->makePayment(billID, dbManager);
            break;
        case 4:
            cout << "Logging out...\n";
            return; // Log out and return to main menu
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
