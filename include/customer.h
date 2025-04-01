#ifndef CUSTOMER_H // header guard
#define CUSTOMER_H // prevent multiple inclusions

#include <iostream>          // for i/o
#include <vector>            // for using vector container
#include <string>            // for using string
#include "bill.h"            // bill class
#include "databaseManager.h" // database management class
#include "UtilityService.h"  // utility service class
#include "provider.h"        // provider class

class DatabaseManager; // forward declaration of DatabaseManager

using namespace std; // use standard namespace

// ************************************************************
//
//  Class: Customer
//
//  Description: represents a customer subscribing to utilities
//
// ************************************************************
class Customer
{
private:
    int customerID;     // customer ID
    string name;        // customer name
    string address;     // customer address
    vector<Bill> bills; // list of bills

public:
    // ************************************************************
    //
    //  Constructor: Customer
    //
    //  Description: creates a new customer object
    //
    // ************************************************************
    Customer(const int &id, const string &name, const string &address);

    // ************************************************************
    //
    //  Function: Getters
    //
    //  Description: returns customer attributes
    //
    // ************************************************************
    int getCustomerID() const { return customerID; } // get customer ID
    string getName() const { return name; }          // get name
    string getAddress() const { return address; }    // get address

    // ************************************************************
    //
    //  Function: subscribeService
    //
    //  Description: subscribes a customer to a service
    //
    // ************************************************************
    void subscribeToService(DatabaseManager &dbManager, vector<UtilityService> &services, vector<provider> &providers, int providerID, int serviceID);

    // ************************************************************
    //
    //  Function: viewBill
    //
    //  Description: allows a user to view their bill
    //
    // ************************************************************
    void viewBill() const;

    // ************************************************************
    //
    //  Function: addBill
    //
    //  Description: adds a bill to the bills list
    //
    // ************************************************************
    void addBill(const Bill &bill);

    // ************************************************************
    //
    //  Function: makePayment
    //
    //  Description: allows a customer to pay a bill
    //
    // ************************************************************
    void makePayment(int billID, DatabaseManager &dbManager);

    // ************************************************************
    //
    //  Function: login
    //
    //  Description: allows user to login to system
    //
    // ************************************************************
    static Customer *login(vector<Customer> &customers, int id);

    // ************************************************************
    //
    //  Function: registerAccount
    //
    //  Description: allows user to register into system
    //
    // ************************************************************
    static Customer *registerAccount(vector<Customer> &customers, int id, const string &name, const string &address, DatabaseManager &dbManager);

    // ************************************************************
    //
    //  Function: loadBillsFromDatabase
    //
    //  Description: loads the bills from the database to be created/updated/viewed
    //
    // ************************************************************
    void loadBillsFromDatabase(DatabaseManager &dbManager);
};

#endif // end of header guard
