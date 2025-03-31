# 3400_Utility_Service_Provider

## Description

This project is a utility service provider management system built in C++ with SQLite for database management.

## Usage

To run this program:

1. Navigate to the 3400_Utility_Service_Provider directory
2. Enter this command into your command line:
   g++ -std=c++20 -Iinclude -Llib src/main.cpp src/customer.cpp src/bill.cpp src/databaseManager.cpp src/UtilityService.cpp src/provider.cpp src/customer_menu.cpp src/provider_menu.cpp -lsqlite3 -o main
3. Execute using:
   ./main

### Access SQLLite Database

sqlite3 utilityproviders.db
<<<<<<< HEAD
To View Tables
   .tables
To View Table Schema
   .schema <table>
To View a Tables Records
   SELECT * FROM <table>
Exit SQLLite
   .exit
=======

#### View Tables

.tables

#### View Table Schema

.schema <table>

#### View Tables Records

SELECT \* FROM <table>

#### Exit SQLLite

.exit
>>>>>>> 8f7931a11fb0cfa8cda89a8f095495776631c4be
