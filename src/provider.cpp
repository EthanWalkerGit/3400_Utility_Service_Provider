#include "provider.h" // include header file

using namespace std; // use standard namespace

// ************************************************************
//
//  Constructor: provider
//
//  Description: creates a new provider object
//
// ************************************************************
provider::provider(int id, string name, double s) : provider_id(id), provider_name(name), sales(s) {}

// ************************************************************
//
//  Function: getName
//
//  Description: gets the name of a provider
//
// ************************************************************
string provider::getName() const { return provider_name; }

// ************************************************************
//
//  Function: get_pid
//
//  Description: gets the provider id of a provider
//
// ************************************************************
int provider::get_pid() const { return provider_id; }
