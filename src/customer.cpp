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
void Customer::subscribeService(DatabaseManager &dbManager)
{
    int billID = bills.size() + 1; // Assign unique bill ID
    int serviceID = billID;        // Placeholder (replace later)
    int providerID = billID;       // Placeholder (replace later)
    double amount = 50.0;          // Placeholder amount
    string dueDate = "2025-04-01"; // Placeholder date
    string status = "Pending";     // Set bill status to pending

    // Insert bill into database
    stringstream query;
    query << "INSERT INTO bills (BillID, CustomerID, ServiceID, ProviderID, Amount, DueDate, Status) VALUES ("
          << billID << ", " << customerID << ", " << serviceID << ", " << providerID << ", " << amount << ", '"
          << dueDate << "', '" << status << "');";

    if (dbManager.executeQuery(query.str())) // Ensure query execution was successful
    {
        bills.push_back(Bill(billID, customerID, serviceID, providerID, amount, dueDate, status));
        cout << "\nService subscribed! New bill generated.\n";
    }
    else
    {
        cout << "\nError: Failed to add bill to database.\n";
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
    // Check if the ID is already taken
    for (const Customer &customer : customers)
    {
        if (customer.getCustomerID() == id)
        {
            cout << "\nCustomer ID already exists! Try logging in.\n";
            return nullptr;
        }
    }

    // Insert new customer into database
    stringstream query;
    query << "INSERT INTO customers (CustomerID, Name, Address) VALUES (" << id << ", '" << name << "', '" << address << "');";

    if (dbManager.executeQuery(query.str())) // Ensure query execution was successful
    {
        customers.emplace_back(id, name, address);
        cout << "\nAccount created successfully!\n";
        return &customers.back();
    }
    else
    {
        cout << "\nError: Failed to register customer in database.\n";
        return nullptr;
    }
}
