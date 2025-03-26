#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include "customer.h"

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
    int billID = dbManager.getNextBillID();     // Assuming the database provides the next available bill ID
    double amount = selectedService->getRate(); // Get rate from the service
    string dueDate = "2025-04-01";              // Placeholder due date (could be dynamically set)
    string status = "Pending";                  // Default status

    // Insert the bill into the database
    stringstream query;
    query << "INSERT INTO bills (BillID, CustomerID, ServiceID, Amount, DueDate, Status) VALUES ("
          << billID << ", " << this->customerID << ", " << selectedService->getSID() << ", " << amount << ", '"
          << dueDate << "', '" << status << "');";

    if (dbManager.executeQuery(query.str()))
    {
        int providerID = 1; // Replace with an actual provider ID if needed
        bills.push_back(Bill(billID, this->customerID, selectedService->getSID(), providerID, amount, dueDate, status));

        cout << "Successfully subscribed to " << selectedService->getName() << " service. New bill generated.\n";
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

    vector<Bill> bills; // Create an empty vector to hold the bills

    // Execute query and fetch results into the vector
    if (!dbManager.executeQuery(query.str(), bills)) // Pass the bills vector to the executeQuery function
    {
        cout << "No bills found for customer " << this->customerID << endl;
        return;
    }

    // Populate the customer's bills vector with the fetched bills
    this->bills = bills;
}
