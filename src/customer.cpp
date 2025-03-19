#include "customer.h" // include header file

// ************************************************************
//
//  Constructor: Customer
//
//  Description: Creates a new customer object.
//
// ************************************************************

Customer::Customer(DatabaseManager &db, const string &name, const string &address)
{
    this->name = name;       // each customer has a name
    this->address = address; // each customer has an address

    // Construct the SQL query string
    string query = "INSERT INTO Customers (name, address) VALUES ('" + name + "', '" + address + "');";

    // Execute the query
    db.executeQuery(query);

    // Retrieve the last inserted customer ID
    this->customerID = db.getLastInsertId();
}

// ************************************************************
//
//  Function: subscribeService
//
//  Description: Subscribes a customer to a placeholder service.
//
// ************************************************************
void Customer::subscribeService()
{
    int billID = bills.size() + 1; // assign unique ID to new bill based on current # of bills
    int serviceID = billID;        // replace with actual service id later
    int providerID = billID;       // replace with actual provider id later
    double amount = 50.0;          // placeholder amount
    string dueDate = "2025-04-01"; // placeholder date
    string status = "default";     // placeholder state

    // create new bill and store it in bills vector
    bills.push_back(Bill(billID, customerID, serviceID, providerID, amount, dueDate, status));
    cout << "\nService subscribed! New bill generated.\n";
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
void Customer::makePayment(int billID)
{
    for (Bill &bill : bills) // loop through all bills in vector
    {
        if (bill.getBillID() == billID) // check if the bill id matches that being paid
        {
            bill.markPaid(); // use the pay function in bill class to attempt to pay the bill
            cout << "\nBill " << billID << " has been paid.\n";
            return;
        }
    }
    cout << "\nBill ID not found.\n"; // no matching bill was found
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
Customer *Customer::registerAccount(vector<Customer> &customers, int id, const string &name, const string &address)
{
    // Check if the ID is already taken
    for (const Customer &customer : customers) // loop through all customers in vector
    {
        if (customer.getCustomerID() == id) // check if the customer id matches
        {
            cout << "\nCustomer ID already exists! Try logging in.\n";
            return nullptr; // return refference to no customer
        }
    }

    cout << "\nAccount created successfully!\n";
    return &customers.back(); // return refference to newly added customer at back of vector
}
