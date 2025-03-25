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

void customer_menu(std::vector<Customer> &customers, std::vector<UtilityService> &services, DatabaseManager &dbManager);
void view_services(std::vector<UtilityService> &services);

#endif
