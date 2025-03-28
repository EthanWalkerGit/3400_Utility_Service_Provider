# 3400_Utility_Service_Provider

## Description

This project is a utility service provider management system built in C++ with SQLite for database management.

## Usage

To run this program:

1. Navigate to the source directory
2. Enter this command into your command line:
   g++ -std=c++20 -Iinclude -Llib src/main.cpp src/customer.cpp src/bill.cpp src/databaseManager.cpp src/UtilityService.cpp src/provider.cpp src/customer_menu.cpp src/provider_menu.cpp  -lsqlite3 -o main
3. Execute using:
   ./main

To Access SQLLite Database
   sqlite3 utilityproviders.db
To View Tables
   .tables
To View Table Schema
   .schema <table>
To View a Tables Records
   SELECT * FROM <table>
Exit SQLLite
   .exit

To run test.cpp

   g++ test.cpp provider.cpp UtilityService.cpp -lsqlite3 -o test


To run test_main.cpp
   g++ -std=c++20 -Iinclude -Llib src/test_main.cpp src/customer.cpp src/bill.cpp src/databaseManager.cpp src/UtilityService.cpp src/provider.cpp  -lsqlite3 -o test_main

./test_main