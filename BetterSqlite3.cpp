#include "BetterSqlite3.h"
#include <vector>
#include <algorithm>
#include <cstdint>
#include <any>
#include <stdexcept>
#include <string>

namespace BetterSqlite3 {
    BetterSqlite3::BetterSqlite3(const std::string &filename): _dbFileName(filename) {
    int res = sqlite3_open(_dbFileName.c_str(), &_db);

    if (res != SQLITE_OK)
        throw std::runtime_error("Failed to open database.");
    }

    BetterSqlite3::~BetterSqlite3() {
        if (_db)
            sqlite3_close(_db);
    }

    std::vector<BetterSqlite3::Row> BetterSqlite3::bindAndExecuteCommand(const std::string &sqlCode, const std::vector<std::string> &params) const {
        sqlite3_stmt* statement = bindCommand(sqlCode, params);

        std::vector<Row> results;
        while (sqlite3_step(statement) == SQLITE_ROW) {
            results.push_back(processRow(statement));
        }

        return results;
    }

    BetterSqlite3::Row BetterSqlite3::processRow(sqlite3_stmt *statement) const {
        BetterSqlite3::Row row;
        int columnCount = sqlite3_column_count(statement);
        for (int i = 0; i < columnCount; ++i) {
            int type = sqlite3_column_type(statement, i);

            switch (type)
            {
                case SQLITE_INTEGER:
                    row.push_back(sqlite3_column_int(statement, i));
                    break;

                case SQLITE_FLOAT:
                    row.push_back(sqlite3_column_double(statement, i));
                    break;

                case SQLITE_TEXT: {
                    const char* text = reinterpret_cast<const char*>(sqlite3_column_text(statement, i));
                    row.push_back(text ? std::string(text) : std::string(""));
                    break;
                }

                case SQLITE_BLOB: {
                    const uint8_t* blobData = reinterpret_cast<const uint8_t*>(sqlite3_column_blob(statement, i));
                    const int size = sqlite3_column_bytes(statement, i);
                    row.push_back(std::vector<uint8_t>(blobData, blobData + size));
                    break;
                }
                
                case SQLITE_NULL:
                default: {
                    row.push_back(nullptr);
                    break;
                }
            }
        }

        return row;
    }
    sqlite3_stmt *BetterSqlite3::bindCommand(const std::string &sqlCode, const std::vector<std::string> &params) const {
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
}
