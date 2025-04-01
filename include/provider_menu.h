#ifndef PROVIDER_MENU
#define PROVIDER_MENU

#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "UtilityService.h"
#include "provider.h"
#include "databaseManager.h"

using namespace std;

void provider_menu(vector<provider> &providers, vector<UtilityService> &services, DatabaseManager &dbManager);
void add_provider(vector<provider> &providers, DatabaseManager &dbManager);

#endif
