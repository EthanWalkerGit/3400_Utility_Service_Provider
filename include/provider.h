#ifndef PROVIDER_H
#define PROVIDER_H

#include <string>
#include <list>
#include <iostream>
#include "UtilityService.h"

using namespace std;

class provider{
public:

	int provider_id;
	string provider_name;
	list<UtilityService> services_offered;

	provider(int id, string name);

	string getName() const;

	int get_pid() const;

};

#endif