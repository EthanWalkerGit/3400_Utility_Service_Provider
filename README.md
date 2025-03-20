# 3400_Utility_Service_Provider

## Description

This project is a utility service provider management system built in C++ with SQLite for database management.

## Usage

To run this program:

1. Navigate to the source directory
2. Enter this command into your command line:

   g++ -std=c++20 -Iinclude -Llib src/main.cpp src/customer.cpp src/bill.cpp src/databaseManager.cpp -lsqlite3 -o main

3. Execute using:
   ./main


To run test.cpp

   g++ test.cpp provider.cpp UtilityService.cpp -lsqlite3 -o test
