#include "customer_menu.h"

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
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
