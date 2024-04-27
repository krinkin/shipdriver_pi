#pragma once

#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Transaction.h>

#include <memory>
#include <string>

namespace MarineNavi {

class DbClient {

public:
    DbClient(std::shared_ptr<SQLite::Database> db): db_(db) {
    }

private:
    std::shared_ptr<SQLite::Database> db_;

};

std::shared_ptr<SQLite::Database> CreateDatabase(std::string dbName);

} // namespace MarineNavi