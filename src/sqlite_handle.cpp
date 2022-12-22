#include "sqlite_handle.h"

#include "build_info.h"

namespace pig_sqlite {

SqliteHandler::SqliteHandler() { m_impl = std::make_shared<SqliteImpl>(); }
SqliteHandler::~SqliteHandler() {}

bool SqliteHandler::init() {
    std::string path = std::string(CURRENT_PATH) + "/data/pig_data.db";
    if (!m_impl->loadDB(path)) {
        return false;
    }
    return true;
}

bool SqliteHandler::setPigSlogan(const std::string& value) {
    m_impl->setSysInfo(SqliteImpl::k_pigSlogan, value);
    return true;
}

bool SqliteHandler::delPigSlogan() {
    return m_impl->delSysInfo(SqliteImpl::k_pigSlogan);
}

std::string SqliteHandler::getPigSlogan() {
    return m_impl->getSysInfo(SqliteImpl::k_pigSlogan);
}

};  // namespace pig_sqlite
