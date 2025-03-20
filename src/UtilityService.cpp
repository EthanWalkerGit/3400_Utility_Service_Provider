#include "UtilityService.h"
using namespace std;

UtilityService::UtilityService(int sid, string sn, double rpu, double fc, int pid)
    : service_id(sid), service_name(sn), rate_per_unit(rpu), fixed_charge(fc), providerID(pid) {}

// ************************************************************
//
//  Function: getRate
//
//  Description: Returns the rate per unit for the service.
//
// ************************************************************

double UtilityService::getRate() const { return rate_per_unit; }

// ************************************************************
//
//  Function: calculateBill
//
//  Description: Calculates the bill for a given usage.
//
// ************************************************************

double UtilityService::calculateBill(double units_used) const { return (rate_per_unit + units_used) + fixed_charge; }

string UtilityService::getName() const { return service_name; }

int UtilityService::getSID() const { return service_id; }

double UtilityService::getFC() const { return fixed_charge; }
