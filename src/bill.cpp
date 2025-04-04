#include "bill.h" // include header file

// ************************************************************
//
//  Constructor: Bill
//
//  Description: Creates a new bill object.
//
// ************************************************************
Bill::Bill(int id, int custID, int servID, int provID, double amt, const string &date, const string &stat)
{
    this->billID = id;         // bills have an id
    this->customerID = custID; // bills have a customer id for the customer it belongs to
    this->serviceID = servID;  // bills have a service id for the service it belongs to
    this->providerID = provID; // bills have a provider id for the provider they belong to
    this->amount = amt;        // bills have a monetary value
    this->dueDate = date;      // bills have a date they must be paid by
    this->status = stat;       // bills have a status (paid or not)
}

// ************************************************************
//
//  Function: Getters
//
//  Description: functions that retrive a specefic attribute of a bill
//
// ************************************************************
int Bill::getBillID() const
{
    return billID; // retrieves id
}
double Bill::getAmount() const
{
    return amount; // retrives current amount on bill
}
string Bill::getDueDate() const
{
    return dueDate; // retrives bills due date
}
string Bill::getStatus() const
{
    return status; // retrives bill status
}
int Bill::getCustomerID() const
{
    return customerID; // retives customer id
}
int Bill::getServiceID() const
{
    return serviceID; // retrives service id
}
int Bill::getProviderID() const
{
    return providerID; // retrives provider id
}

// ************************************************************
//
//  Function: markPaid
//
//  Description: marks the bill as paid
//
// ************************************************************
void Bill::markPaid()
{
    if (status == "paid") // check if the bill is already paid
    {
        cout << "\nBill " << billID << " is already paid.\n";
    }
    else // bill is not paid
    {
        status = "paid"; // mark bill as paid
        cout << "\nBill " << billID << " has been marked as paid.\n";
    }
}
