# Better SQLite3 Library
A modern C++ wrapper for the SQLite3 API.

# How to Use
### Add Files to Your Project
Include the following files in your project:
* `sqlite3.c/h` - the original SQLite API source files.
* `BetterSqlite3.cpp/h` - the modern wrapper.

### Usage
Construct the modern SQLite object:
```cpp
BetterSqlite3 database("path/to/your/database.sqlite");
```

Execute a query and use the returned vector of vectors:
```cpp
auto table = database.bindAndExecuteCommand("SQL CODE", {param1, param2, ...});
```

> [!IMPORTANT]
> To use safe parameters, make sure each parameter placeholder is represented by `?` and that the parameters are provided in the vector in the correct order.

> [!TIP]
> The query returns a `std::vector<std::vector<std::any>>`, where each inner vector represents a row and each item is stored as a `std::any`. Use `std::any_cast<type>(...)` to convert a value to the desired type.

# Thanks and Info
For questions or changes, please contact me at `noam2009r@gmail.com`.
