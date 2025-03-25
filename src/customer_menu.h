#ifndef CUSTOMER_MENU
#define CUSTOMER_MENU

#include <vector>
#include <iostream>
#include "UtilityService.h"
#include "customer.h"
#include "databaseManager.h"

class Customer;
class DatabaseManager;

using namespace std;

void customer_menu(vector<Customer> &customers, vector<UtilityService> &services, DatabaseManager &dbManager);

#endif
