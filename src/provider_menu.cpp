#include "provider_menu.h" // include header

// ************************************************************
//
//  Function: setRate
//
//  Description: sets the rate of a service per unit
//
// ************************************************************
double setRate()
{
    double rate;                                    // var for rate
    cout << "Please set the rate per unit price: "; // prompt rate
    cin >> rate;                                    // receive user input for rate
    return rate;                                    // return rate
}

// ************************************************************
//
//  Function: setFC
//
//  Description: sets the fixed cost of a service
//
// ************************************************************
double setFC()
{
    double fc;                             // var for fixed cost
    cout << "Please set the fixed cost: "; // prompt fixed cost
    cin >> fc;                             // receive user input for fixed cost
    return fc;                             // return fixed cost
}

// ************************************************************
//
//  Function: view_services
//
//  Description: displays all available services filtering by provider
//
// ************************************************************
void view_services(vector<UtilityService> &services, vector<provider> &providers, int pid = -1)
{
    string provider_name = "All Providers";

    if (pid != -1) // find provider name if a specific provider is selected
    {
        for (const auto &p : providers) // iterate over providers
        {
            if (p.get_pid() == pid) // cjeck if provider id matches
            {
                provider_name = p.getName(); // retrive the provider name
                break;
            }
        }
    }
    cout << "\n--- " << provider_name << "'s Available Services ---\n"; // provider name header
    for (const auto &service : services)                                // iterate over services
    {
        if (pid == -1 || service.getPID() == pid) // show all or filtered services
        {
            cout << "Service ID: " << service.getSID()
                 << " | Name: " << service.getName()
                 << " | Rate: $" << service.getRate() << "/unit"
                 << " | Fixed Cost: $" << service.getFC() << endl;
        }
    }
}

// ************************************************************
//
//  Function: view_sales
//
//  Description: retrieves and displays the total sales for a provider
//
// ************************************************************
void view_sales(vector<provider> &providers, int pid, DatabaseManager &dbManager)
{
    double sales = 0.0;                                                          // var to hold sales value
    stringstream query_ss;                                                       // query var
    query_ss << "SELECT Sales FROM providers WHERE providerID = " << pid << ";"; // query to get sales for a provider
    const string query = query_ss.str();

    vector<vector<string>> result = dbManager.executeQuery(query, true); // call executeQuery and get the result

    if (!result.empty() && !result[0].empty()) // check if the result contains valid data
    {
        sales = stod(result[0][0]); // convert the first sales value to a double
    }

    cout << "\nTotal Sales for Provider ID " << pid << ": $" << sales << endl; // diplay sales
}

// ************************************************************
//
//  Function: add_service
//
//  Description: allows a provider to add a new service to their offerings
//
// ************************************************************
void add_service(vector<UtilityService> &services, vector<provider> &providers, int pid, DatabaseManager &dbManager)
{
    int opp;            // holder user option
    string servicename; // holds service name
    double rate;        // holds rate
    double fc;          // holds fixed cost

    while (true) // loop until user enters exit
    {
        cout << "\n---Select a Service Category---\n"; // options of services to add
        cout << "1. Natural Gas\n";
        cout << "2. Internet Service\n";
        cout << "3. Hydro\n";
        cout << "4. Go Back\n";
        cout << "Enter Option: ";

        cin >> opp; // get input

        if (cin.fail()) // check for invalid input
        {
            cin.clear();                                         // clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input! Please enter a valid number.\n";
            continue; // ask for input again
        }

        if (opp == 1) // natural gas category has no subcategories
        {
            servicename = "Natural Gas";
            rate = setRate();
            fc = setFC();
        }
        else if (opp == 2) // internet has 4 subcategpories to choose from
        {
            cout << "\n1. TV\n";
            cout << "2. Mobile Phone\n";
            cout << "3. Home Phone\n";
            cout << "4. Go Back\n";
            cout << "Enter Option: ";

            cin >> opp; // get input

            if (cin.fail()) // check for invalid input
            {
                cin.clear();                                         // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input! Please enter a valid number.\n";
                continue; // ask for input again
            }

            if (opp == 1) // if-else block for differnt internet subcategory options
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
            else if (opp == 4)
            {
                continue; // go back to the main menu
            }
        }

        else if (opp == 3) // hydro has 3 subcategories
        {
            cout << "\n1. Electric\n";
            cout << "2. Water\n";
            cout << "3. Sewerage\n";
            cout << "4. Go Back\n";
            cout << "Enter Option: ";

            cin >> opp; // get input

            if (cin.fail()) // check for invalid input
            {
                cin.clear();                                         // clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input! Please enter a valid number.\n";
                continue; // ask for input again
            }

            if (opp == 1) // if-else block for differnt hydro subcategory options
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
            else if (opp == 4)
            {
                continue; // go back to the main menu
            }
        }
        else if (opp == 4)
        {
            return; // exit the function if "Go Back" is chosen
        }
        else
        {
            cout << "Invalid choice. Please select a valid option.\n";
            continue; // ask for input again if invalid choice is made
        }

        stringstream query_ss; // query var
        query_ss << "INSERT INTO services (S_Name, rate_per_unit, fixed_charge, providerID) VALUES ('"
                 << servicename << "', " << rate << ", " << fc << ", " << pid << ");"; // query to insert new service
        const string query = query_ss.str();
        dbManager.executeQuery(query); // execute query using db function

        int sid = (services.back().getSID()) + 1;               // get next service ID
        services.emplace_back(sid, servicename, rate, fc, pid); // update local service conatiner
        break;                                                  // break out of the loop after adding the service
    }
}

// ************************************************************
//
//  Function: edit_service
//
//  Description: edit an existing service's rate and fixed charge
//
// ************************************************************
void edit_service(vector<UtilityService> &services, vector<provider> &providers, int pid, DatabaseManager &dbManager)
{
    int sid;       // service id
    double rate;   // rate
    double fc;     // fixed cost
    int check = 0; // flag to check if the service exists
    while (true)   // loop to cintinue until user exits
    {
        cout << "Enter ServiceID to set new rate per unit and fixed cost(or 0 to go back): ";
        cin >> sid;   // get input
        if (sid == 0) // if back
        {
            return;
        }
        for (const auto &s : services) // iterate over services
        {
            if (s.getPID() == pid && s.getSID() == sid) // check if provider id matches
            {
                check = 1; // flag that service exists
            }
        }
        if (check == 1) // check flag to see if service exists
        {
            break;
        }
        cout << "try again\n";
    }

    rate = setRate();      // set the new rate
    fc = setFC();          // set the new fixed cost
    stringstream query_ss; // query var
    query_ss << "UPDATE services SET rate_per_unit=" << rate << ", fixed_charge = " << fc << " WHERE serviceID = " << sid << ";";
    const string query = query_ss.str(); // query to update a service
    dbManager.executeQuery(query);       // call execute query function

    for (auto &s : services) // iterate over services
    {
        if (s.getPID() == pid && s.getSID() == sid) // check if provider id matches
        {
            s.edit(rate, fc); // update locally with edit function
        }
    }
}

// ************************************************************
//
//  Function: deleteService
//
//  Description: deletes a providers service
//
// ************************************************************
void deleteService(vector<UtilityService> &services, vector<provider> &providers, int pid, DatabaseManager &dbManager)
{
    int sid;        // service id
    int index = 0;  // index in conatiner
    int count = -1; // counter

    while (true)
    {
        cout << "Enter ServiceID of the service you would like to delete: ";
        cin >> sid; // get input
        index = 0;
        count = -1;
        for (const auto &s : services) // iterate over services
        {
            if (s.getPID() == pid && s.getSID() == sid) // check if provider id matches
            {
                count = index; // mark index
                break;
            }
            index++; // update counter
        }

        if (count != -1) // if counter was modfied exit
        {
            break;
        }
        cout << "Service not found, try again.\n";
    }

    stringstream query_ss;                                               // query var
    query_ss << "DELETE FROM services WHERE serviceID = " << sid << ";"; // query to delete a service record
    const string query = query_ss.str();
    dbManager.executeQuery(query);            // execute query with function
    services.erase(services.begin() + count); // delete locally from conatiner
}

// ************************************************************
//
//  Function: provider_menu
//
//  Description: cli user input menu for provider options
//
// ************************************************************
void provider_menu(vector<provider> &providers, vector<UtilityService> &services, DatabaseManager &dbManager)
{
    int pid;              // provider id
    int exit_loop;        // flag to mark if loop should be exited
    int count = 0;        // counter to count attempts
    int opp;              // user input option
    string provider_name; // stores a provider name

    while (true) // iterate utill user exits
    {
        cout << "Enter Provider ID: "; // prompt password (provider id)
        cin >> pid;                    // get password (provider id)

        if (cin.fail()) // check for invalid input
        {
            cin.clear();                                         // clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input! Please enter a valid number.\n";
            continue; // ask for input again
        }

        for (const auto &p : providers) // iterate over providers
        {
            if (p.get_pid() == pid) // check if provider id matches
            {
                exit_loop = 1;               // mark flag to exit
                provider_name = p.getName(); // provider name retrieval
                break;
            }
        }

        if (exit_loop == 1) // if provider was found exit loop
        {
            break; // exit loop
        }
        if (count == 3) // if there are 3 attempts counted
        {
            return; // exit after 3 failed attempts
        }
        cout << "Try again\n";
        count++; // increment attempt counter
    }

    cout << "\nWelcome back, " << provider_name << "!\n"; // welcome message

    do // do while loop to iterate over provider options until exit is selected
    {
        cout << "\n--- Service Menu ---\n";
        cout << "1. View Services\n";  // view the providers services
        cout << "2. Add Service\n";    // make a new service for the provider
        cout << "3. Edit Service\n";   // edit an existing provider service
        cout << "4. Delete Service\n"; // delete an exisiting service for the provider
        cout << "5. View Sales\n";     // view the total sales of a provider
        cout << "6. Exit\n";           // exit menu
        cout << "Enter your choice: "; // prompt choice
        cin >> opp;                    // recive user input choice

        if (cin.fail()) // check for invalid input
        {
            cin.clear();                                         // clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input! Please enter a valid number.\n";
            continue; // ask for input again
        }

        switch (opp) // switch statement to handle different options the user may have picked
        {
        case 1:
            view_services(services, providers, pid);
            break;
        case 2:
            add_service(services, providers, pid, dbManager);
            break;
        case 3:
            edit_service(services, providers, pid, dbManager);
            break;
        case 4:
            deleteService(services, providers, pid, dbManager);
            break;
        case 5:
            view_sales(providers, pid, dbManager);
            break;
        case 6:
            cout << "Exiting menu..." << endl;
            break;
        default: // if none of the options are selected
            cout << "Enter a valid choice\n";
            continue; // continue to ask for valid input if an invalid option is entered
        }

    } while (opp != 6); // contine loop until exit option is picked
}

// ************************************************************
//
//  Function: add_provider
//
//  Description: handles adding a new provider (registration)
//
// ************************************************************
void add_provider(vector<provider> &providers, DatabaseManager &dbManager)
{
    string providername;              // new provider name
    cout << "\nEnter Company Name: "; // prompt for name
    cin.ignore();                     // ignore unwanted parts of input
    getline(cin, providername);       // get name

    stringstream query_ss;                                                                 // query var
    query_ss << "INSERT INTO providers (P_name) VALUES (" << "'" << providername << "');"; // query to insert new provider
    const string query = query_ss.str();
    dbManager.executeQuery(query);              // execute query using function in db manager
    int pid = (providers.back().get_pid()) + 1; // update local providers conatiner
    providers.emplace_back(pid, providername, 0);
    cout << "Your provider login key is " << pid << endl; // display the new provider id so they know what to login with
}
