#ifndef UTILITYSERVICE_H // prevent multiple inclusions
#define UTILITYSERVICE_H // define header guard

#include <iostream> // for i/o

using namespace std; // use standard namespace

// ************************************************************
//
//  Class: UtilityService
//
//  Description: represents a service offered by a provider
//			     which a customer subscribes to and bills are generate for
//
// ************************************************************
class UtilityService
{
private:
	int service_id;		  // unique identfer for a service
	string service_name;  // name for a service
	double rate_per_unit; // rate of a service
	double fixed_charge;  // fixed charge of a service
	int providerID;		  // provider id the service is linked to (provider that offers the service)

public:
	// ************************************************************
	//
	//  Constructor: UtilityService
	//
	//  Description: initializes a utility service object
	//
	// ************************************************************
	UtilityService(int sid, string sn, double rpu, double fc, int pid);

	// ************************************************************
	//
	//  Destructor: ~UtilityService
	//
	//  Description: destructs memory for utility service object
	//
	// ************************************************************
	~UtilityService();

	// ************************************************************
	//
	//  Function: Getters
	//
	//  Description: retrives a specefic attribute of a service
	//
	// ************************************************************
	double getRate() const; // get rate
	string getName() const; // get name
	int getSID() const;		// get service id
	double getFC() const;	// get fixed cost
	int getPID() const;		// get provider id

	// ************************************************************
	//
	//  Function: calculateBill
	//
	//  Description: calculates the value for a bill
	//
	// ************************************************************
	double calculateBill(double units_used) const;

	// ************************************************************
	//
	//  Function: edit
	//
	//  Description: allows the modification of a service
	//
	// ************************************************************
	void edit(double new_rate, double new_fc);
};
#endif
