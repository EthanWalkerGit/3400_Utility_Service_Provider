#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <vector>
#include <string>
#include "bill.h"
#include "databaseManager.h"

using namespace std;

// ************************************************************
//
//  Class: Customer
//
//  Description: Represents a customer subscribing to utilities.
//
// ************************************************************
class Customer
{
private:
    int customerID;
    string name;
    string address;
    vector<Bill> bills; // Stores the customer's bills

public:
    // ************************************************************
    //
    //  Constructor: Customer
    //
    //  Description: Creates a new customer object.
    //
    // ************************************************************
    Customer(DatabaseManager &db, const string &name, const string &address);

    // ************************************************************
    //
    //  Function: getter functions
    //
    //  Description: Returns customer attributes
    //
    // ************************************************************
    int getCustomerID() const { return customerID; }
    string getName() const { return name; }
    string getAddress() const { return address; }

    // ************************************************************
    //
    //  Function: subscribeService
    //
    //  Description: Subscribes a customer to a placeholder service.
    //
    // ************************************************************
    void subscribeService();

    // ************************************************************
    //
    //  Function: viewBill
    //
    //  Description: Allows a user to view their bill status.
    //
    // ************************************************************
    void viewBill() const;

    // ************************************************************
    //
    //  Function: makePayment
    //
    //  Description: Allows a customer to pay a bill.
    //
    // ************************************************************
    void makePayment(int billID);

    // Login/Register Functions
    static Customer *login(vector<Customer> &customers, int id);
    static Customer *registerAccount(vector<Customer> &customers, int id, const string &name, const string &address);
};

#endif
