#include "BetterSqlite3.h"
#include <iostream>

class User {
public:
    User(const std::string& name, int age): _age(age), _name(name) {}

    std::string getUserInformation() const {
        return "Name: " + _name + "\nAge: " + std::to_string(_age);
    }
private:
    std::string _name;
    int _age;    
};

int main() {
    
    BetterSqlite3::BetterSqlite3 db("database.sqlite"); // opens / creates the database

    /*
    Run the SQLite command with no params:
    CREATE TABLE Users (name TEXT);
    */
    db.bindAndExecuteCommand("CREATE TABLE IF NOT EXISTS Users (name TEXT, age INTEGER);", {}); // ingores the return due to now return from SQLite.

    /*
    Runs the SQLite command with name and age as params:
    INSERT INTO Users (name, age) VALUES (?, ?);
    */
    const std::string name = "noam";
    const int age = 17;
    db.bindAndExecuteCommand("INSERT INTO Users (name, age) VALUES (?, ?);", {name, std::to_string(age)});

    /*
    Runs the SQLite command with no params:
    SELECT * FROM Users;
    */
    auto table = db.bindAndExecuteCommand("SELECT * FROM Users;", {});

    /*
    Assign users for each row and adds it to the vector
    */
    std::vector<User> users;
    for (auto row : table) {
        users.push_back({std::any_cast<std::string>(row[0]), std::any_cast<int>(row[1])});
    }

    /*
    Prints all the users in the vector.
    */
    for (auto user : users) {
        std::cout << user.getUserInformation() << std::endl;
    }
}

