#include "../BetterSqlite3.h"
#include <iostream>

int main() {
    BetterSqlite3::BetterSqlite3 db("database.sqlite"); // opens / creates the database

    /*
    Run the SQlite Command with no params:
    CREATE TABLE Users (name TEXT);
    */
    db.bindAndExecuteCommand("CREATE TABLE IF NOT EXISTS Users (name TEXT);", {}); // ingores the return due to now return from SQLite.

    /*
    Runs the Sqlite Command with name as param:
    INSERT INTO Users (name) VALUES (?);
    */
   std::string name = "noam";
   db.bindAndExecuteCommand("INSERT INTO Users (name) VALUES (?);", {name});
}

