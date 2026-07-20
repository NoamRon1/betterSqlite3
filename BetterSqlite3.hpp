extern "C" {
    #include "sqlite3.h"
}
#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <algorithm>

namespace BetterSqlite3 {
    class BetterSqlite3 {

    public:
        BetterSqlite3(const std::string& filename): _dbFileName(filename) {
            std::ifstream file(filename);
            if (!file.is_open())
                throw std::runtime_error("File not found: " + filename);

            int res = sqlite3_open(_dbFileName.c_str(), &_db);

            if (res != SQLITE_OK)
                throw std::runtime_error("Failed to open database.");
        }

        ~BetterSqlite3() {
            if (_db)
                sqlite3_close(_db);
        }

    public:
        template<class r_type>
        r_type bindAndExecuteCommand(const std::string& sqlCode, r_type(*processingFunction)(sqlite3_stmt*), const std::vector<std::string>& params) const {
            sqlite3_stmt* statement = bindCommand(sqlCode, params);
            return processingFunction(statement);
        }

        sqlite3_stmt* bindCommand(const std::string& sqlCode, const std::vector<std::string>& params) const {
            if (!_db)
                throw std::runtime_error("Database is closed!");
            
            sqlite3_stmt* statement;

            if (params.size() != std::count(sqlCode.begin(), sqlCode.end(), '?'))
                throw std::invalid_argument("Argument count does not match the sql code.");

            int status = sqlite3_prepare_v2(_db, sqlCode.c_str(), -1, &statement, nullptr);
            if (status != SQLITE_OK) {
                std::string error = sqlite3_errmsg(_db);
                throw std::runtime_error("SQLite prepare error: " + error);
            }

            for (int i = 0; i < params.size(); i++) {
                status = sqlite3_bind_text(statement, i + 1, params[i].c_str(), -1, SQLITE_STATIC);
                if (status != SQLITE_OK) {
                    std::string error = sqlite3_errmsg(_db);
                    sqlite3_finalize(statement);
                    throw std::runtime_error("SQLite bind error: " + error);
                }
            }

            return statement;
        }

    private:
        sqlite3* _db = nullptr;
        std::string _dbFileName;
    };
};