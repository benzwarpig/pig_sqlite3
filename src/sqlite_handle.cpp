#include "sqlite_handle.h"

#include "build_info.h"
#include "pig_serialize.hpp"
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

std::string SqliteHandler::getMapMarkInfo(const std::string& mapId,
                                          const std::string& markType) {
    return m_impl->getMapMarkInfo(mapId, markType);
}

bool SqliteHandler::delMapMarkInfo(const std::string& mapId) {
    return m_impl->delMapMarkInfo(mapId);
}

void SqliteHandler::setAreaMarkInfo(const std::string& mapId,
                                    AreaMarkType areaType,
                                    const std::vector<Point2D>& points) {
    using pig_util::pig_serialize::PigSerialize;
    PigSerialize<Point2D> pigSerialize;
    std::vector<char> tmpPoints = pigSerialize.serializeToVector(points);
    m_impl->setAreaMarkInfo(mapId, areaType, tmpPoints);
}

std::vector<Point2D> SqliteHandler::getAreaMarkInfo(const std::string& mapId,
                                                    AreaMarkType areaType) {
    using pig_util::pig_serialize::PigSerialize;
    PigSerialize<Point2D> pigSerialize;
    auto points = m_impl->getAreaMarkInfo(mapId, areaType);
    if (points.size() != 0) {
        return pigSerialize.unserializeToVector(points);
    }
    return {};
}

bool SqliteHandler::delAreaMarkInfo(const std::string& mapId,
                                    AreaMarkType areaType) {
    return m_impl->delAreaMarkInfo(mapId, areaType);
}

};  // namespace pig_sqlite
