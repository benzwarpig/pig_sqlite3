#include "sqlite_handle.h"

#include "build_info.h"
#include "rng_builder.hpp"

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

void SqliteHandler::setMapMarkInfo(const std::string& mapId,
                                   const std::string& markType,
                                   const std::string& commit) {
    MapMarkInfo markInfo;
    markInfo.markId = RAND_INT(100000);
    markInfo.mapId = mapId;
    markInfo.markType = markType;
    m_impl->setMapMarkInfo(markInfo, commit);
}

bool SqliteHandler::delMapMarkInfo(const std::string& mapId) {
    return m_impl->delMapMarkInfo(mapId);
}

};  // namespace pig_sqlite
