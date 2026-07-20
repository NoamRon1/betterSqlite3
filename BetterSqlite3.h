extern "C" {
    #include "sqlite3.h"
}

#include <string>
#include <vector>
#include <any>

namespace BetterSqlite3 {
    class BetterSqlite3 {

    public:
        BetterSqlite3(const std::string& filename);

        ~BetterSqlite3();

        using Row = std::vector<std::any>;

    public:
        std::vector<Row> bindAndExecuteCommand(const std::string& sqlCode, const std::vector<std::string>& params) const;

    private:
        sqlite3* _db = nullptr;
        std::string _dbFileName;

    private:
        Row processRow(sqlite3_stmt* statement) const;

        sqlite3_stmt* bindCommand(const std::string& sqlCode, const std::vector<std::string>& params) const;
    };
};