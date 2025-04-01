#include "customer.h" // include header

#include <vector>   // for vector conatiner
#include <map>      // for map container
#include <string>   // string manipulation
#include <iostream> // for i/o
#include <sstream>  // string stream operations
#include <ctime>    // date/time functions
#include <iomanip>  // output formatting

// ************************************************************
//
//  Constructor: Customer
//
//  Description: creates a new customer object
//
// ************************************************************
Customer::Customer(const int &id, const string &name, const string &address)
{
    this->name = name;       // each customer has a name
    this->address = address; // each customer has an address
    this->customerID = id;   // each customer has an id
}

// ************************************************************
//
//  Function: subscribeService
//
//  Description: subscribes a customer to a service
//
// ************************************************************
void Customer::subscribeToService(DatabaseManager &dbManager, vector<UtilityService> &services, vector<provider> &providers, int providerID, int serviceID)
{
    cout << "\n--- " << providers[providerID].getName() << "'s Available Services ---\n"; // provider name header

    vector<UtilityService *> availableServices; // vector to hold services
    for (auto &service : services)              // iterate over services
    {
        if (service.getPID() == providerID) // check if the provider id matches
        {
            availableServices.push_back(&service);                                // add service to list
            cout << service.getSID() << ". " << service.getName() << " - Rate: $" // display service details
                 << service.getRate() << "/unit, Fixed Cost: $" << service.getFC() << endl;
        }
    }

    bool serviceFound = false;                 // flag to mark if a service is found
    UtilityService *selectedService = nullptr; // pointer for a service

    for (auto &service : availableServices) // iterate over availible services found
    {
        if (service->getSID() == serviceID) // find the service with the entered ID
        {
            selectedService = service; // mark the service found
            serviceFound = true;       // mark flag as found
            break;                     // exit loop
        }
    }

    if (!serviceFound) // if the service was not found amongst the availible ones
    {
        cout << "Invalid Service ID. Please try again.\n"; // print error message
        return;
    }

    double amount = selectedService->getRate(); // get rate of selected service
    time_t now = time(nullptr);                 // get current time in seconds
    tm *ltm = localtime(&now);                  // convert current time to local time
    ltm->tm_mday += 30;                         // add 30 days to the current day to set due date
    mktime(ltm);                                // normalize the time structure (adjust for month/year overflow)

    string dueDate = to_string(ltm->tm_year + 1900) + "-" + (ltm->tm_mon < 9 ? "0" : "") + to_string(ltm->tm_mon + 1) + "-" + (ltm->tm_mday < 10 ? "0" : "") + to_string(ltm->tm_mday); // format due date as "YYYY-MM-DD"

    string status = "Pending"; // set initial status to "Pending" before it is paid

    stringstream query; // variable to hold query
    query << "INSERT INTO bills (CustomerID, ServiceID, Amount, DueDate, Status) VALUES ("
          << this->customerID << ", " << selectedService->getSID() << ", " << amount << ", '"
          << dueDate << "', '" << status << "');"; // query to insert a new bill

    if (dbManager.executeQuery(query.str())) // call execute query function in dbManager class
    {
        int billID = dbManager.getLastInsertId();                                                                        // retrive from the db the last bill id to determine the bill id for the new bill
        bills.push_back(Bill(billID, this->customerID, selectedService->getSID(), providerID, amount, dueDate, status)); // add new bill to vector

        cout << "Successfully subscribed to " << selectedService->getName() << " service! New bill (Bill ID: " << billID << ") created.\n"; // success message
    }
    else
    {
        cout << "Error: Failed to create a new bill.\n"; // query failed message
    }
}

// ************************************************************
//
//  Function: viewBill
//
//  Description: allows a user to view their bill status
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
//  Function: addBill
//
//  Description: Adds a bill to the bills list.
//
// ************************************************************
void Customer::addBill(const Bill &bill)
{
    bills.push_back(bill); // add a new bill to bills conatiner
}

// ************************************************************
//
//  Function: makePayment
//
//  Description: allows a customer to pay a bill
//
// ************************************************************
void Customer::makePayment(int billID, DatabaseManager &dbManager)
{
    for (Bill &bill : bills) // iterate over bills
    {
        if (bill.getBillID() == billID) // check if bill exists
        {
            double amount = bill.getAmount();      // get bills value
            int providerID = bill.getProviderID(); // get proivder id associated with bill

            bill.markPaid(); // update the bill status

            stringstream updateBillQuery;                                                           // query var
            updateBillQuery << "UPDATE bills SET Status = 'Paid' WHERE BillID = " << billID << ";"; // query to update bill status

            if (dbManager.executeQuery(updateBillQuery.str())) // call execute query
            {
                stringstream updateSalesQuery; // query var
                updateSalesQuery << "UPDATE providers SET Sales = Sales + " << amount
                                 << " WHERE providerID = " << providerID << ";"; // query to update the provider sales since a bill is paid

                if (dbManager.executeQuery(updateSalesQuery.str())) // check if successful
                {
                    cout << "\nBill " << billID << " has been paid successfully. Provider sales updated.\n"; // success message
                }
                else
                {
                    cout << "\nError: Failed to update provider sales.\n"; // update failed message
                }
            }
            else // databse update failed
            {
                cout << "\nError: Failed to update bill status in database.\n"; // update failed message
            }
            return;
        }
    }
    cout << "\nError: Bill ID not found.\n"; // bill not found error message
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
            cout << "\nLogin successful! Welcome back, " << customer.getName() << ".\n"; // print out customer name
            return &customer;                                                            // return refference to customer
        }
    }
    cout << "\nCustomer ID not found. Please register.\n"; // error message
    return nullptr;                                        // return refference to no customer
}

// ************************************************************
//
//  Function: registerAccount
//
//  Description: If the user doesn't exist, they can create a new account
//
// ************************************************************
Customer *Customer::registerAccount(vector<Customer> &customers, int id, const string &name, const string &address, DatabaseManager &dbManager)
{
    stringstream query;                                                                                        // query var
    query << "INSERT INTO Customers (customer_name, address) VALUES ('" << name << "', '" << address << "');"; // insert new customer into database query

    if (dbManager.executeQuery(query.str())) // call execute query
    {
        int newID = dbManager.getLastInsertId(); // get new customer id from db

        customers.emplace_back(newID, name, address);                                     // add new customer to customer conatiner
        cout << "\nAccount created successfully! Your Customer ID is: " << newID << "\n"; // success message
        return &customers.back();
    }
    else
    {
        cout << "\nError: Failed to register customer in database.\n"; // failed to register message
        return nullptr;
    }
}

// ************************************************************
//
//  Function: loadBillsFromDatabase
//
//  Description: Loads all the bills for a customer from the database.
//
// ************************************************************
void Customer::loadBillsFromDatabase(DatabaseManager &dbManager)
{
    stringstream query;                                                                                                     // query var
    query << "SELECT BillID, ServiceID, Amount, DueDate, Status FROM bills WHERE CustomerID = " << this->customerID << ";"; // query to get bills

    vector<Bill> bills; // vector conatiner to hold bills

    if (!dbManager.executeQuery(query.str(), bills)) // call execute query and check if it fails
    {
        cout << "No bills found for customer " << this->customerID << endl; // error message for query failing
        return;
    }

    time_t now = time(0);                      // get current time in seconds since epoch
    tm currentDate = *localtime(&now);         // convert current time to local time structure
    currentDate.tm_hour = 0;                   // set hour to 0 (midnight)
    currentDate.tm_min = 0;                    // set minute to 0
    currentDate.tm_sec = 0;                    // set second to 0
    time_t currentTime = mktime(&currentDate); // convert modified tm struct back to time_t (midnight time)

    for (auto &bill : bills) // iterate over bills
    {
        if (bill.getStatus() == "paid") // skip if paid
        {
            continue;
        }

        tm dueTm = {};                               // create an empty tm structure to store the parsed date
        istringstream dateStream(bill.getDueDate()); // create an input string stream from the bill's due date
        dateStream >> get_time(&dueTm, "%Y-%m-%d");  // parse the date in "YYYY-MM-DD" format into the tm structure
        time_t dueTime = mktime(&dueTm);             // convert the parsed tm structure into time_t

        if (dueTime < currentTime) // compare dates to see if overdue
        {
            Bill overdueBill(
                bill.getBillID(),
                this->customerID,
                bill.getServiceID(),
                bill.getProviderID(),
                bill.getAmount(),
                bill.getDueDate(),
                "Overdue"); // new bill with updated status of overdue

            bill = overdueBill; // replace the bill in the vector

            stringstream updateQuery;                                                                        // query var
            updateQuery << "UPDATE bills SET Status = 'Overdue' WHERE BillID = " << bill.getBillID() << ";"; // update database query
            dbManager.executeQuery(updateQuery.str());                                                       // call execute query
        }
    }

    this->bills = bills; // update bills list
}