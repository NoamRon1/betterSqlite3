#include "BetterSqlite3.h"
#include <iostream>

int main() {
    
    BetterSqlite3::BetterSqlite3 db("database.sqlite"); // opens / creates the database

    /*
    Run the SQLite command with no params:
    CREATE TABLE Users (name TEXT);
    */
    db.bindAndExecuteCommand("CREATE TABLE IF NOT EXISTS Users (name TEXT);", {}); // ingores the return due to now return from SQLite.

    /*
    Runs the SQLite command with name as param:
    INSERT INTO Users (name) VALUES (?);
    */
    std::string name = "noam";
    db.bindAndExecuteCommand("INSERT INTO Users (name) VALUES (?);", {name});

    /*
    Runs the SQLite command with no params:
    SELECT * FROM Users;
    */
    auto table = db.bindAndExecuteCommand("SELECT * FROM Users;", {});

    /*
    Prints every item in every row.
    */
    for (auto row : table) {
        for (auto item : row) {
            std::cout << std::any_cast<std::string>(item) << std::endl; // make sure to cast the any item to the desired object (std::string in this case)
        }
    }
}

