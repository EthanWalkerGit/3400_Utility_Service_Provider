#include "UtilityService.h"
using namespace std;



UtilityService::UtilityService(int sid, string sn, double rpu, double fc , int pid)
	: service_id(sid), service_name(sn), rate_per_unit(rpu), fixed_charge(fc), providerID(pid){}

UtilityService::~UtilityService(){}

double UtilityService::getRate()const { return rate_per_unit;}



double UtilityService::calculateBill(double units_used) const{ return (rate_per_unit + units_used) + fixed_charge;}


string UtilityService::getName() const {return service_name;}


int UtilityService::getSID() const {return service_id;}

double UtilityService::getFC()const { return fixed_charge;}

int UtilityService::getPID() const {return providerID;}

void UtilityService::edit (double new_rate, double new_fc) {
	rate_per_unit = new_rate;
	fixed_charge = new_fc;

}

