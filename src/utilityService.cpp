#ifndef UTILITYSERVICE_H
#define UTILITYSERVICE_H

#include <iostream>
using namespace std;

// ************************************************************
//
//  Class: utilityService
//
//  Description: Represents a general utility service.
//
// ************************************************************
class utilityService
{
private:
    int serviceID;
    string serviceName;
    double ratePerUnit;
    double fixedCharge;

public:
    // ************************************************************
    //
    //  Constructor: utilityService
    //
    //  Description: Creates a utility service object.
    //
    // ************************************************************
    utilityService(int id, const string &name, double rate, double charge);

    // ************************************************************
    //
    //  Function: getRate
    //
    //  Description: Returns the rate per unit for the service.
    //
    // ************************************************************
    double getRate();

    // ************************************************************
    //
    //  Function: calculateBill
    //
    //  Description: Calculates the bill for a given usage.
    //
    // ************************************************************
    double calculateBill(double usage);
};

#endif
