#include "provider_menu.h"

double setRate()
{
    double rate;
    cout << "Please set the rate per unit price: ";
    cin >> rate;
    return rate;
}
double setFC()
{

    double fc;
    cout << "Please set the fixed cost: ";
    cin >> fc;
    return fc;
}

void view_services(vector<UtilityService> services, int pid)
{
    cout << "\n---Current Services ---\n";
    for (const auto &s : services)
    {
        if (s.getPID() == pid)
        {
            cout << "\nService id:" << s.getSID() << "----Service Name " << s.getName() << "----Rate: " << s.getRate() << "----Fixed Cost: " << s.getFC() << endl;
        }
    }
}

void add_service(vector<UtilityService> &services, vector<provider> &providers, int pid, DatabaseManager &dbManager)
{

    int opp;
    string servicename;
    double rate;
    double fc;

    cout << "\n---Select a Service Category---\n";
    cout << "1. Natural Gas\n";
    cout << "2. Internet Service\n";
    cout << "3. Hydro\n";
    cout << "Enter Option: ";
    cin >> opp;

    if (opp == 1)
    {
        servicename = "Natural Gas";
        rate = setRate();
        fc = setFC();
    }
    else if (opp == 2)
    {
        opp = 0;
        cout << "\n1. TV\n";
        cout << "2. Mobile Phone\n";
        cout << "3. Home Phone\n";
        cout << "Enter Option: ";

        cin >> opp;
        if (opp == 1)
        {
            servicename = "TV";
            rate = setRate();
            fc = setFC();
        }
        else if (opp == 2)
        {
            servicename = "Mobile Phone";
            rate = setRate();
            fc = setFC();
        }

        else if (opp == 3)
        {
            servicename = "Home Phone";
            rate = setRate();
            fc = setFC();
        }
    }

    else if (opp == 3)
    {
        opp = 0;
        cout << "\n1. Electric\n";
        cout << "2. Water\n";
        cout << "3. Sewerage\n";
        cout << "Enter Option: ";

        cin >> opp;
        if (opp == 1)
        {
            servicename = "Electric";
            rate = setRate();
            fc = setFC();
        }
        else if (opp == 2)
        {
            servicename = "Water";
            rate = setRate();
            fc = setFC();
        }

        else if (opp == 3)
        {
            servicename = "Sewerage";
            rate = setRate();
            fc = setFC();
        }
    }

    stringstream query_ss;
    query_ss << "INSERT INTO services (S_Name, rate_per_unit, fixed_charge, providerID) VALUES (" << "'" << servicename << "'" << "," << rate << "," << fc << "," << pid << ");";
    const string query = query_ss.str();
    dbManager.executeQuery(query);
    int sid = (services.back().getSID()) + 1;
    services.emplace_back(sid, servicename, rate, fc, pid);
}

void edit_service(vector<UtilityService> &services, vector<provider> &providers, int pid, DatabaseManager &dbManager)
{
    int sid;
    double rate;
    double fc;
    int check = 0;
    while (true)
    {
        cout << "Enter ServiceID to set new rate per unit and fixed cost: ";
        cin >> sid;

        for (const auto &s : services)
        {
            if (s.getPID() == pid && s.getSID() == sid)
            {
                check = 1;
            }
        }
        if (check == 1)
        {
            break;
        }
        cout << "try again\n";
    }

    rate = setRate();
    fc = setFC();
    stringstream query_ss;
    query_ss << "UPDATE services SET rate_per_unit=" << rate << ", fixed_charge = " << fc << " WHERE serviceID = " << sid << ";";
    const string query = query_ss.str();
    dbManager.executeQuery(query);

    for (auto &s : services)
    {
        if (s.getPID() == pid && s.getSID() == sid)
        {

            s.edit(rate, fc);
        }
    }
}
void deleteService(vector<UtilityService> &services, vector<provider> &providers, int pid, DatabaseManager &dbManager)
{
    int sid;
    int index = 0;
    int count = -1;
    while (true)
    {
        cout << "Enter ServiceID of the service you would like to delete: ";
        cin >> sid;
        index = 0;
        count = -1;
        for (const auto &s : services)
        {
            if (s.getPID() == pid && s.getSID() == sid)
            {
                count = index;
                break;
            }
            index++;
        }

        if (count != -1)
        {
            break;
        }
        cout << "Service not found, try again.\n";
    }
    stringstream query_ss;
    query_ss << "DELETE FROM services WHERE serviceID = " << sid << ";";
    const string query = query_ss.str();
    dbManager.executeQuery(query);
    services.erase(services.begin() + count);
}

void provider_menu(vector<provider> &providers, vector<UtilityService> &services, DatabaseManager &dbManager)
{

    int pid;
    int exit_loop = 0;
    int count = 0;
    int opp;
    while (true)
    {

        cout << "Enter Password: ";
        cin >> pid;

        for (const auto &p : providers)
        {
            if (p.get_pid() == pid)
            {
                exit_loop = 1;
                break;
            }
        }
        if (exit_loop == 1)
        {
            break;
        }
        if (count == 3)
        {
            return;
        }
        cout << "try again\n";
        count++;
    }

    do
    {
        cout << "\n--- Service Menu ---\n";
        cout << "1. View Services\n";
        cout << "2. Add Service\n";
        cout << "3. Edit Service\n";
        cout << "4. Delete Service\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> opp;

        if (opp == 1)
        {
            view_services(services, pid);
        }
        else if (opp == 2)
        {
            add_service(services, providers, pid, dbManager);
        }
        else if (opp == 3)
        {
            edit_service(services, providers, pid, dbManager);
        }
        else if (opp == 4)
        {
            deleteService(services, providers, pid, dbManager);
        }
        else if (opp == 5)
        {
            cout << "exiting menu..." << endl;
        }
        else
        {
            cout << "enter vaild choice\n";
            continue;
        }

    } while (opp != 5);
}