#ifndef PROVIDER_H
#define PROVIDER_H

#include <iostream>
#include <list>
#include "utilityService.h"

using namespace std;

// ************************************************************
//
//  Class: provider
//
//  Description: Represents a company providing utilities.
//
// ************************************************************
class provider
{
private:
    int providerID;
    string providerName;
    list<utilityService *> servicesOffered;

public:
    // ************************************************************
    //
    //  Constructor: provider
    //
    //  Description: Creates a utility provider.
    //
    // ************************************************************
    provider(int id, const string &name);

    // ************************************************************
    //
    //  Function: addService
    //
    //  Description: Adds a utility service to the provider.
    //
    // ************************************************************
    void addService(utilityService *service);

    // ************************************************************
    //
    //  Function: getServiceRate
    //
    //  Description: Retrieves the rate for a given service.
    //
    // ************************************************************
    double getServiceRate(int serviceID);

    // ************************************************************
    //
    //  Function: listAllServices
    //
    //  Description: Displays all services offered by the provider.
    //
    // ************************************************************
    void listAllServices();
};

#endif
