#include "customer_menu.h"
#include "customer.h"
#include "databaseManager.h"
#include "provider_menu.h"

void view_services(std::vector<UtilityService> &services)
{
    cout << "\n--- Available Services ---\n";
    for (const auto &service : services)
    {
        cout << "Service ID: " << service.getSID()
             << " | Name: " << service.getName()
             << " | Rate: " << service.getRate()
             << " | Fixed Cost: " << service.getFC() << endl;
    }
}

void customer_menu(vector<Customer> &customers, vector<UtilityService> &services, DatabaseManager &dbManager)
{
    int customerID;

    cout << "Enter Customer ID: ";
    cin >> customerID;

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
        cout << "1. Subscribe to a service\n";
        cout << "2. View bills\n";
        cout << "3. Make a payment\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // Display the available services for the customer to choose from
            view_services(services); // Assuming you pass the services list here
            // After viewing, allow subscription to a selected service
            customer->subscribeToService(dbManager, services);
            break;
        case 2:
            customer->viewBill();
            break;
        case 3:
            int billID;
            cout << "Enter Bill ID to pay: ";
            cin >> billID;
            customer->makePayment(billID, dbManager);
            break;
        case 4:
            cout << "Logging out...\n";
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
