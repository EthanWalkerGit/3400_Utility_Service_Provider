#include "provider.h"

using namespace std;


provider::provider(int id, string name, double s) : provider_id(id) , provider_name(name), sales(s){}

string provider::getName() const {return provider_name;}

int provider::get_pid() const { return provider_id;}

