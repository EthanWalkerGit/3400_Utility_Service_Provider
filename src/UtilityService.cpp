#include "UtilityService.h" // include header file

using namespace std; // use standard namespace

// ************************************************************
//
//  Constructor: UtilityService
//
//  Description: initializes a utility service object
//
// ************************************************************
UtilityService::UtilityService(int sid, string sn, double rpu, double fc, int pid)
	: service_id(sid), service_name(sn), rate_per_unit(rpu), fixed_charge(fc), providerID(pid) {}

// ************************************************************
//
//  Destructor: ~UtilityService
//
//  Description: destructs memory for utility service object
//
// ************************************************************
UtilityService::~UtilityService() {}

// ************************************************************
//
//  Function: Getters
//
//  Description: retrives a specefic attribute of a service
//
// ************************************************************
double UtilityService::getRate() const
{
	return rate_per_unit;
}
string UtilityService::getName() const
{
	return service_name;
}
int UtilityService::getSID() const
{
	return service_id;
}
double UtilityService::getFC() const
{
	return fixed_charge;
}
int UtilityService::getPID() const
{
	return providerID;
}

// ************************************************************
//
//  Function: calculateBill
//
//  Description: calculates the value for a bill
//
// ************************************************************
double UtilityService::calculateBill(double units_used) const
{
	return (rate_per_unit + units_used) + fixed_charge; // bill is calculated by adding the rate per unit times the units used with the fixed charge
}

// ************************************************************
//
//  Function: edit
//
//  Description: allows the modification of a service
//
// ************************************************************
void UtilityService::edit(double new_rate, double new_fc)
{
	rate_per_unit = new_rate; // set new rate
	fixed_charge = new_fc;	  // set new fixed charge
}
