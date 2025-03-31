#ifndef BILL_H
#define BILL_H

#include <iostream>

using namespace std;

// ************************************************************
//
//  Class: Bill
//
//  Description: Tracks customer payments.
//
// ************************************************************
class Bill
{
private:
    int billID;
    int customerID;
    int serviceID;
    int providerID;
    double amount;
    string dueDate;
    string status; // "paid" or "default"

public:
    // ************************************************************
    //
    //  Constructor: Bill
    //
    //  Description: Creates a new bill object.
    //
    // ************************************************************
    Bill(int id, int custID, int servID, int provID, double amt, const string &date, const string &stat);

    // Getters
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
    //  Description: Marks the bill as paid.
    //
    // ************************************************************
    void markPaid();
};

#endif
