#ifndef UTILITYSERVICE_H
#define UTILITYSERVICE_H
#include <iostream>
using namespace std;

class UtilityService{
private:
	int service_id;
	string service_name;
	double rate_per_unit;
	double fixed_charge;
	int providerID;
public:
	UtilityService(int sid, string sn,double rpu, double fc, int pid);
	~UtilityService();
	
	double getRate() const;

	double calculateBill(double units_used) const;

	string getName() const;

	int getSID() const;

	double getFC() const;

	int getPID() const;

	void edit(double new_rate, double new_fc);
};
#endif
