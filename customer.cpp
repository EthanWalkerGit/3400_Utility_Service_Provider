#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>

using namespace std;

// ************************************************************
//
//  Class: customer
//
//  Description: Represents a customer subscribing to utilities.
//
// ************************************************************
class customer
{
private:
    int customerID;
    string name;
    string address;

public:
    // ************************************************************
    //
    //  Constructor: customer
    //
    //  Description: Creates a new customer object.
    //
    // ************************************************************
    customer(int id, const string &name, const string &address);

    // ************************************************************
    //
    //  Function: subscribeService
    //
    //  Description: Subscribes a customer to a service.
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
    void viewBill();

    // ************************************************************
    //
    //  Function: makePayment
    //
    //  Description: Allows a customer to pay a bill.
    //
    // ************************************************************
    void makePayment();
};

#endif
