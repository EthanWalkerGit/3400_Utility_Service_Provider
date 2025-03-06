#include <string>

using namespace std;

class utilityService
{
    int serviceID;
    string serviceName;
    double ratePerUnit;
    double fixedCharge;

public:
    // Default Constructor
    utilityService() : serviceID(0), serviceName(" "), ratePerUnit(0), fixedCharge(0) {}
    // Constructor
    // utilityService(int sid, string sName, double rate, double ?)

    double getRate()
    {
        return ratePerUnit;
    };
    double calculateBill()
    {
        return fixedCharge;
    }
};

int main()
{

    return 0;
}