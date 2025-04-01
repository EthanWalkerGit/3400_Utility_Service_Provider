#ifndef CUSTOMER_MENU // header guard
#define CUSTOMER_MENU // prevent multiple inclusions

#include <vector>            // for using vector container
#include <iostream>          // for i/o
#include "UtilityService.h"  // include utility service class
#include "customer.h"        // include customer class
#include "databaseManager.h" // include database manager class
#include "provider.h"        // include provider class

class Customer;        // forward declaration of customer class
class DatabaseManager; // forward declaration of database manager class
class provider;        // forward declaration of provider class

using namespace std; // use standard namespace

// ************************************************************
//
//  Function: customer_menu
//
//  Description: displays the menu for customers to interact with
//
// ************************************************************
void customer_menu(std::vector<Customer> &customers, std::vector<UtilityService> &services, std::vector<provider> &providers, DatabaseManager &dbManager);

// ************************************************************
//
//  Function: view_services
//
//  Description: displays available services, optionally filtered by provider
//
// ************************************************************
void view_services(std::vector<UtilityService> &services, int providerID = -1);

#endif