#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <vector>
#include <string>
#include "bill.h"
#include "databaseManager.h"
#include "UtilityService.h"
#include "provider.h"

class DatabaseManager;

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
    Customer(const int &id, const string &name, const string &address);

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
    void subscribeToService(DatabaseManager &dbManager, vector<UtilityService> &services, vector<provider> &providers, int providerID, int serviceID);

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
    //  Function: addBill
    //
    //  Description: Adds a bill to the bills list.
    //
    // ************************************************************
    void addBill(const Bill &bill);

    // ************************************************************
    //
    //  Function: makePayment
    //
    //  Description: Allows a customer to pay a bill.
    //
    // ************************************************************
    void makePayment(int billID, DatabaseManager &dbManager);

    // Login/Register Functions
    static Customer *login(vector<Customer> &customers, int id);
    static Customer *registerAccount(vector<Customer> &customers, int id, const string &name, const string &address, DatabaseManager &dbManager);

    // load bills function
    void loadBillsFromDatabase(DatabaseManager &dbManager);
};

#endif
