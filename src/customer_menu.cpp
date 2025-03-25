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
    int id;
    Customer *currentCustomer = nullptr;

    cout << "Enter Customer ID: ";
    cin >> id;

    currentCustomer = Customer::login(customers, id);

    if (!currentCustomer)
    {
        cout << "Invalid ID! Returning to main menu.\n";
        return;
    }

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
            currentCustomer->subscribeToService(dbManager, services);
            break;
        case 2:
            currentCustomer->viewBill();
            break;
        case 3:
            int billID;
            cout << "Enter Bill ID to pay: ";
            cin >> billID;
            currentCustomer->makePayment(billID, dbManager);
            break;
        case 4:
            cout << "Logging out...\n";
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
