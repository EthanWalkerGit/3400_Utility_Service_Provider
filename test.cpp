#include <sqlite3.h>
#include "UtilityService.h"
#include "provider.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;






    void LoadData(vector<provider>& providers, vector<UtilityService>& services) {
        sqlite3* db;
        if (sqlite3_open("usp_database.db", &db)) {
            cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
            return;
        }
    
        const char* sql = "SELECT providers.providerID, providers.P_Name, services.serviceID, services.S_Name, services.rate_per_unit, services.fixed_charge FROM providers JOIN services ON providers.providerID = services.providerID;";
        sqlite3_stmt* stmt;
    
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return;
        }
    
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int pid = sqlite3_column_int(stmt, 0);
            string p_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int sid = sqlite3_column_int(stmt, 2);
            string s_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            double rpu = sqlite3_column_double(stmt, 4);
            double fc = sqlite3_column_double(stmt, 5);
            providers.emplace_back(pid, p_name);
            services.emplace_back(sid, s_name, rpu,fc,pid);
        }


    
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
    
    void print_services(string servicename,vector<UtilityService>& services){
        cout << "id --- Service Name --- Rate --- Fixed charge" << endl;
        for (const auto& s : services) {
            if (s.getName() == servicename){
                cout << s.getSID() << " ----- " << s.getName() << " ----- " << s.getRate() << " ----- " << s.getFC() << endl;
            }
            
        }


    }







int main(){
        
        vector<provider> providers;
        vector<UtilityService> services;


        LoadData(providers , services);

       
       
     
        int opp;
        cout << "\n---Select a Service Category---\n";
        cout << "1. Natural Gas\n";
        cout << "2. Internet Service\n";
        cout << "3. Hydro\n";
        cout << "Enter Option: ";
        cin >> opp;


        if(opp == 1){
            print_services("Natural Gas",services);

        }
        else if(opp == 2){
            opp = 0;
            cout << "\n1. TV\n";
            cout << "2. Mobile Phone\n";
            cout << "3. Home Phone\n";
            cout << "Enter Option: ";

            cin >> opp;
            if(opp == 1){
                print_services("TV",services);
    
            }
            else if(opp == 2){
                print_services("Mobile Phone",services);
    
            }
    
            else if (opp == 3){
                print_services("Home Phone",services);
    
            }
        }

        else if (opp == 3){
            opp = 0;
            cout << "\n1. Electric\n";
            cout << "2. Water\n";
            cout << "3. Sewerage\n";
            cout << "Enter Option: ";

            cin >> opp;
            if(opp == 1){
                print_services("Electric",services);
    
            }
            else if(opp == 2){
                print_services("Water",services);
    
            }
    
            else if (opp == 3){
                print_services("Sewerage",services);
    
            }
        }


    return 0;



}