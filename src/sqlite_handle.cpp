#include "sqlite_handle.h"

#include "build_info.h"

namespace pig_sqlite {

SqliteHandler::SqliteHandler() { m_impl = std::make_shared<SqliteImpl>(); }
SqliteHandler::~SqliteHandler() {}

bool SqliteHandler::init() {
    std::string path = std::string(CURRENT_PATH) + "/pig_data.db";
    if (!m_impl->loadDB(path)) {
        return false;
    }
    return true;
}

};  // namespace pig_sqlite
