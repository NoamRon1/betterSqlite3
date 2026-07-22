# Better SQLite3 Library
A modern `c++` wrapper for the `sqlite3` api.

# How to use
### Add files to project
Add this files to your project:
* sqlite3.c/h - the old api files.
* BetterSqlite3.cpp/h - the modern wrapper.

### How to use in your code
Constract the modern sqlite object:
```cpp
BetterSqlite3 database("path/to/your/database.sqlite");
```
<br/>
Send queries to the database and use the returned vector of vectors.

```cpp
auto table = database.bindAndExecuteCommand("SQL CODE", {param1, param2, ...})
```

> [!IMPORTANT] to use `safe parameters` make sure you include `?` for each parameter placement. Make sure to include the parameters in the vector in the right order!

> [!TIP] the query returns a vector of vectors representing rows and items inside the rows. Each item is a `std::any` object. To convert it to the desired type use `std::any_cast<type>(...)`.

# Thanks and Info
For questions and changes, you may contact me at: `noam2009r@gmail.com`.
