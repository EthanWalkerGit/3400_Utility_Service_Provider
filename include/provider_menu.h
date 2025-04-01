#ifndef PROVIDER_MENU // prevent multiple inclusions
#define PROVIDER_MENU // define header guard

#include <vector>            // for using vectors
#include <iostream>          // for i/o
#include <sstream>           // for string stream operations
#include <algorithm>         // for algorithms like sort
#include "UtilityService.h"  // include utility service class
#include "provider.h"        // include provider class
#include "databaseManager.h" // include database manager class

using namespace std; // use standard namespace

// ************************************************************
//
//  Function: provider_menu
//
//  Description: cli user input menu for provider options
//
// ************************************************************
void provider_menu(vector<provider> &providers, vector<UtilityService> &services, DatabaseManager &dbManager);

// ************************************************************
//
//  Function: add_provider
//
//  Description: handles adding a new provider (registration)
//
// ************************************************************
void add_provider(vector<provider> &providers, DatabaseManager &dbManager);

#endif
