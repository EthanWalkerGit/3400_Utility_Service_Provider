#ifndef BILL_H // header guard
#define BILL_H // prevent multiple inclusions

#include <iostream> // for i/o

using namespace std; // use standard namespace

// ************************************************************
//
//  Class: Bill
//
//  Description: tracks customer payments.
//
// ************************************************************
class Bill
{
private:
    int billID;     // unique identifier for a bill
    int customerID; // identifier to the customer who owns the bill
    int serviceID;  // identifier to which service the bill is generated from
    int providerID; // identifier to which provider the bill is generated from
    double amount;  // value of bill to be paid
    string dueDate; // due date of bill
    string status;  // state of bill "paid" or "pending"

public:
    // ************************************************************
    //
    //  Constructor: Bill
    //
    //  Description: creates a new bill object.
    //
    // ************************************************************
    Bill(int id, int custID, int servID, int provID, double amt, const string &date, const string &stat);

    // ************************************************************
    //
    //  Function: Getters
    //
    //  Description: functions that retrive a specefic attribute of a bill
    //
    // ************************************************************
    int getBillID() const;
    double getAmount() const;
    string getDueDate() const;
    string getStatus() const;
    int getCustomerID() const;
    int getServiceID() const;
    int getProviderID() const;

    // ************************************************************
    //
    //  Function: markPaid
    //
    //  Description: marks the bill as paid
    //
    // ************************************************************
    void markPaid();
};

#endif
