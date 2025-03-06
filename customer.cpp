#include <iostream>

using namespace std;

// ************************************************************
//
//	Class: customer
//
// 	Description: read orders from file
//
// ************************************************************
class Customer
{
private:
    int customerID;
    string name;
    string address;

public:
    // ************************************************************
    //
    //	Constructor: customer
    //
    // 	Description: creates a new customer object
    //
    // ************************************************************
    Customer(int id, const string &name, const string &address);

    // ************************************************************
    //
    //	Function: subscribeService
    //
    // 	Description: subscribes a customer to a service
    //
    // ************************************************************
    void subscribeService();

    // ************************************************************
    //
    //	Function: viewBill
    //
    // 	Description: allows a user to view their bill status
    //
    // ************************************************************
    void viewBill();

    // ************************************************************
    //
    //	Function: makePayment
    //
    // 	Description: allows a customer to pay a bill
    //
    // ************************************************************
    void makePayment();
};