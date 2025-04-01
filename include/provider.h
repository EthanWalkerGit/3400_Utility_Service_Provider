#ifndef PROVIDER_H // prevent multiple inclusions
#define PROVIDER_H // define header guard

#include <string>			// for strings
#include <list>				// for using lists
#include <iostream>			// for i/o
#include "UtilityService.h" // include utility service class

using namespace std; // use standard namespace

// ************************************************************
//
//  Class: provider
//
//  Description: represents a provider who offers services to customers
//
// ************************************************************
class provider
{
public:
	int provider_id;					   // provider unqiyue identifier
	string provider_name;				   // provider name
	double sales;						   // providers sales
	list<UtilityService> services_offered; // conatiner for a providers services

	// ************************************************************
	//
	//  Constructor: provider
	//
	//  Description: creates a new provider object
	//
	// ************************************************************
	provider(int id, string name, double s);

	// ************************************************************
	//
	//  Function: getName
	//
	//  Description: gets the name of a provider
	//
	// ************************************************************
	string getName() const;

	// ************************************************************
	//
	//  Function: get_pid
	//
	//  Description: gets the provider id of a provider
	//
	// ************************************************************
	int get_pid() const;
};

#endif
