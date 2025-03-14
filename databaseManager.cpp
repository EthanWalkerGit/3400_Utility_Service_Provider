#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <iostream>

using namespace std;

// ************************************************************
//
//  Class: databaseManager
//
//  Description: Handles database operations.
//
// ************************************************************
class databaseManager
{
public:
    // ************************************************************
    //
    //  Function: saveData
    //
    //  Description: Saves customer, provider, and billing data.
    //
    // ************************************************************
    void saveData();

    // ************************************************************
    //
    //  Function: loadData
    //
    //  Description: Loads data from the database.
    //
    // ************************************************************
    void loadData();

    // ************************************************************
    //
    //  Function: updatePaymentStatus
    //
    //  Description: Updates a customer's payment status.
    //
    // ************************************************************
    void updatePaymentStatus(int billID, const string &status);
};

#endif
