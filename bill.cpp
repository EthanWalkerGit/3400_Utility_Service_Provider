#ifndef BILL_H
#define BILL_H

#include <iostream>

using namespace std;

// ************************************************************
//
//  Class: bill
//
//  Description: Tracks customer payments.
//
// ************************************************************
class bill
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
    //  Constructor: bill
    //
    //  Description: Creates a new bill object.
    //
    // ************************************************************
    bill(int id, int custID, int servID, int provID, double amt, const string &date, const string &stat);

    // ************************************************************
    //
    //  Function: generateBill
    //
    //  Description: Generates a bill for a customer.
    //
    // ************************************************************
    void generateBill();

    // ************************************************************
    //
    //  Function: checkOverdue
    //
    //  Description: Checks if a bill is overdue.
    //
    // ************************************************************
    bool checkOverdue();

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
