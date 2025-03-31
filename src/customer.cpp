#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <ctime> // Required for date/time functions
#include "customer.h"
#include <ctime>
#include <iomanip>
#include <sstream>

// ************************************************************
//
//  Constructor: Customer
//
//  Description: Creates a new customer object.
//
// ************************************************************

Customer::Customer(const int &id, const string &name, const string &address)
{
    this->name = name;       // each customer has a name
    this->address = address; // each customer has an address
    this->customerID = id;
}

// ************************************************************
//
//  Function: subscribeService
//
//  Description: Subscribes a customer to a placeholder service.
//
// ************************************************************
/* original version to diplay all services for all companies
void Customer::subscribeToService(DatabaseManager &dbManager, vector<UtilityService> &services)
{
    int serviceID;
    cout << "Enter the Service ID to subscribe to: ";
    cin >> serviceID;

    // Find the selected service
    UtilityService *selectedService = nullptr;
    for (auto &service : services)
    {
        if (service.getSID() == serviceID)
        {
            selectedService = &service;
            break;
        }
    }

    if (!selectedService)
    {
        cout << "Service not found. Returning to the menu.\n";
        return;
    }

    // Create a new bill for this service
    double amount = selectedService->getRate(); // Get rate from the service

    // Get the current date + 30 days as YYYY-MM-DD
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    ltm->tm_mday += 30; // Add 30 days to the current date
    mktime(ltm);        // Normalize the date structure (handles overflow)
    string dueDate = to_string(ltm->tm_year + 1900) + "-" + (ltm->tm_mon < 9 ? "0" : "") + to_string(ltm->tm_mon + 1) + "-" + (ltm->tm_mday < 10 ? "0" : "") + to_string(ltm->tm_mday);

    string status = "Pending"; // Default status

    // Insert the bill into the database WITHOUT specifying billID
    stringstream query;
    query << "INSERT INTO bills (CustomerID, ServiceID, Amount, DueDate, Status) VALUES ("
          << this->customerID << ", " << selectedService->getSID() << ", " << amount << ", '"
          << dueDate << "', '" << status << "');";

    if (dbManager.executeQuery(query.str()))
    {
        // Retrieve the newly inserted bill ID
        int billID = dbManager.getLastInsertId(); // Fetch last inserted ID from SQLite
        int providerID = 1;                       // Replace with an actual provider ID if needed

        // Store in the local bill list
        bills.push_back(Bill(billID, this->customerID, selectedService->getSID(), providerID, amount, dueDate, status));

        cout << "Successfully subscribed to " << selectedService->getName() << " service. New bill generated (Bill ID: " << billID << ").\n";
    }
    else
    {
        cout << "Error: Failed to create a new bill.\n";
    }
}*/
void Customer::subscribeToService(DatabaseManager &dbManager, vector<UtilityService> &services, vector<provider> &providers, int providerID, int serviceID)
{
    // No need to display the provider list again or ask the user to choose a provider
    cout << "\n--- " << providers[providerID].getName() << "'s Available Services ---\n";

    vector<UtilityService *> availableServices;
    for (auto &service : services)
    {
        if (service.getPID() == providerID)
        {
            availableServices.push_back(&service);
            cout << service.getSID() << ". " << service.getName() << " - Rate: $"
                 << service.getRate() << "/unit, Fixed Cost: $" << service.getFC() << endl;
        }
    }

    bool serviceFound = false;
    UtilityService *selectedService = nullptr;

    // Find the service with the entered ID
    for (auto &service : availableServices)
    {
        if (service->getSID() == serviceID)
        {
            selectedService = service;
            serviceFound = true;
            break;
        }
    }

    if (!serviceFound)
    {
        cout << "Invalid Service ID. Please try again.\n";
        return;
    }

    // Generate a new bill
    double amount = selectedService->getRate();
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    ltm->tm_mday += 30;
    mktime(ltm);
    string dueDate = to_string(ltm->tm_year + 1900) + "-" + (ltm->tm_mon < 9 ? "0" : "") + to_string(ltm->tm_mon + 1) + "-" + (ltm->tm_mday < 10 ? "0" : "") + to_string(ltm->tm_mday);
    string status = "Pending";

    stringstream query;
    query << "INSERT INTO bills (CustomerID, ServiceID, Amount, DueDate, Status) VALUES ("
          << this->customerID << ", " << selectedService->getSID() << ", " << amount << ", '"
          << dueDate << "', '" << status << "');";

    if (dbManager.executeQuery(query.str()))
    {
        int billID = dbManager.getLastInsertId();
        bills.push_back(Bill(billID, this->customerID, selectedService->getSID(), providerID, amount, dueDate, status));
        cout << "Successfully subscribed to " << selectedService->getName() << " service! New bill (Bill ID: " << billID << ") created.\n";
    }
    else
    {
        cout << "Error: Failed to create a new bill.\n";
    }
}

// ************************************************************
//
//  Function: viewBill
//
//  Description: Allows a user to view their bill status.
//
// ************************************************************
void Customer::viewBill() const
{
    if (bills.empty()) // check if there are no bills in the vector
    {
        cout << "\nNo bills available.\n";
        return;
    }

    for (const Bill &bill : bills) // loop through all bills in vector
    {
        cout << "\nBill ID: " << bill.getBillID() // display the bills attributes
             << ", Amount: $" << bill.getAmount()
             << ", Due: " << bill.getDueDate()
             << ", Status: " << bill.getStatus() << endl;
    }
}

// ************************************************************
//
//  Function: addBill
//
//  Description: Adds a bill to the bills list.
//
// ************************************************************
void Customer::addBill(const Bill &bill)
{
    bills.push_back(bill);
}

// ************************************************************
//
//  Function: makePayment
//
//  Description: Allows a customer to pay a bill. (**NOTE NEED TO HANDLE PAYMENT FAILURE**)
//
// ************************************************************
void Customer::makePayment(int billID, DatabaseManager &dbManager)
{
    for (Bill &bill : bills)
    {
        if (bill.getBillID() == billID) // Check if bill exists
        {
            bill.markPaid(); // Update the bill in memory

            // Update the bill status in the database
            stringstream query;
            query << "UPDATE bills SET Status = 'Paid' WHERE BillID = " << billID << ";";

            if (dbManager.executeQuery(query.str()))
            {
                cout << "\nBill " << billID << " has been paid successfully.\n";
            }
            else
            {
                cout << "\nError: Failed to update bill status in database.\n";
            }
            return;
        }
    }
    cout << "\nError: Bill ID not found.\n";
}

// ************************************************************
//
//  Function: login
//
//  Description: Checks if a customer exists by their ID
//
// ************************************************************
Customer *Customer::login(vector<Customer> &customers, int id)
{
    for (Customer &customer : customers) // loop through all customers in vector
    {
        if (customer.getCustomerID() == id) // check if the customer id matches
        {
            cout << "\nLogin successful! Welcome back, " << customer.getName() << ".\n";
            return &customer; // return refference to customer
        }
    }
    cout << "\nCustomer ID not found. Please register.\n";
    return nullptr; // return refference to no customer
}

// ************************************************************
//
//  Function: registerAccount
//
//  Description: If the user doesn't exist, they can create a new account
//
// ************************************************************
Customer *Customer::registerAccount(vector<Customer> &customers, int id, const string &name, const string &address, DatabaseManager &dbManager)
{
    // Insert new customer into database
    stringstream query;
    query << "INSERT INTO Customers (customer_name, address) VALUES ('" << name << "', '" << address << "');";

    if (dbManager.executeQuery(query.str())) // Ensure query execution was successful
    {
        // Retrieve the newly inserted customer ID
        int newID = dbManager.getLastInsertId(); // Use your existing method

        // Add to local customer list
        customers.emplace_back(newID, name, address);
        cout << "\nAccount created successfully! Your Customer ID is: " << newID << "\n";
        return &customers.back();
    }
    else
    {
        cout << "\nError: Failed to register customer in database.\n";
        return nullptr;
    }
}

// ************************************************************
//
//  Function: loadBillsFromDatabase
//
//  Description: Loads all the bills for a customer from the database.
//
// ************************************************************
void Customer::loadBillsFromDatabase(DatabaseManager &dbManager)
{
    stringstream query;
    query << "SELECT BillID, ServiceID, Amount, DueDate, Status FROM bills WHERE CustomerID = " << this->customerID << ";";

    vector<Bill> bills;

    if (!dbManager.executeQuery(query.str(), bills))
    {
        cout << "No bills found for customer " << this->customerID << endl;
        return;
    }

    // Get current date (today at midnight)
    time_t now = time(0);
    tm currentDate = *localtime(&now);
    currentDate.tm_hour = 0;
    currentDate.tm_min = 0;
    currentDate.tm_sec = 0;
    time_t currentTime = mktime(&currentDate);

    for (auto &bill : bills)
    {
        // Skip if already paid
        if (bill.getStatus() == "paid")
        {
            continue;
        }

        // Parse the due date
        tm dueTm = {};
        istringstream dateStream(bill.getDueDate());
        dateStream >> get_time(&dueTm, "%Y-%m-%d");
        time_t dueTime = mktime(&dueTm);

        // Compare dates
        if (dueTime < currentTime)
        {
            // Create a new bill with updated status
            Bill overdueBill(
                bill.getBillID(),
                this->customerID,
                bill.getServiceID(),
                bill.getProviderID(),
                bill.getAmount(),
                bill.getDueDate(),
                "Overdue");

            // Replace the bill in the vector
            bill = overdueBill;

            // Update database
            stringstream updateQuery;
            updateQuery << "UPDATE bills SET Status = 'Overdue' WHERE BillID = " << bill.getBillID() << ";";
            dbManager.executeQuery(updateQuery.str());
        }
    }

    this->bills = bills;
}