#include <pig_sqlite.h>

#include "rng_builder.hpp"

namespace pig_sqlite {
using namespace sqlite_orm;  // NOLINT

SqliteImpl::SqliteImpl() {}
SqliteImpl::~SqliteImpl() {}

auto SqliteImpl::getStorage() {
    // 新增表格或删除表格不会导致数据库重建
    auto storage = make_storage(
        m_dbName,
        // 系统信息字典
        make_table("table_sys_info",
                   make_column("name", &SysInfo::name, primary_key()),
                   make_column("value", &SysInfo::value)),
        make_table("table_map_mark_info",
                   make_column("markId", &MapMarkInfo::markId, autoincrement(),
                               primary_key()),
                   make_column("mapId", &MapMarkInfo::mapId),
                   make_column("markType", &MapMarkInfo::markType),
                   make_column("commit", &MapMarkInfo::commit)),
        make_table("table_area_mark_info",
                   make_column("areaId", &AreaMarkInfo::areaId, autoincrement(),
                               primary_key()),
                   make_column("mapId", &AreaMarkInfo::mapId),
                   make_column("areaType", &AreaMarkInfo::areaType),
                   make_column("areaData", &AreaMarkInfo::areaData)));
    return storage;
}

bool SqliteImpl::loadDB(const std::string& dbName) {
    if (m_isLoad) {
        return true;
    }
    if (dbName.empty()) {
        m_dbName = ":memory:";
    }
    m_dbName = dbName;
    m_isLoad = true;
    auto storage = getStorage();
    storage.sync_schema(true);
    std::cout << "load m_dbName : " << m_dbName << std::endl;
    return true;
}

void SqliteImpl::setSysInfo(const std::string& name, const std::string& value) {
    auto storage = getStorage();
    SysInfo sysInfo{name, value};
    storage.replace(sysInfo);
}

bool SqliteImpl::delSysInfo(const std::string& name) {
    auto storage = getStorage();
    storage.remove_all<SysInfo>(where(c(&SysInfo::name) == name));
    return true;
}

std::string SqliteImpl::getSysInfo(const std::string& name) {
    auto storage = getStorage();
    auto sysInfoPtr = storage.get_pointer<SysInfo>(name);
    if (sysInfoPtr) {
        return sysInfoPtr->value;
    }
    return "";
}

std::map<std::string, std::string> SqliteImpl::getSysInfo() {
    std::map<std::string, std::string> kvmap;
    auto storage = getStorage();
    auto result = storage.get_all_pointer<SysInfo>();
    for (auto& rec : result) {
        kvmap.emplace(rec->name, rec->value);
    }
    return kvmap;
}

void SqliteImpl::setMapMarkInfo(const MapMarkInfo& info,
                                const std::string& commit) {
    auto storage = getStorage();
    MapMarkInfo tmp;
    tmp.commit.clear();
    tmp.markId = info.markId;
    auto markInfos = storage.get_all_pointer<MapMarkInfo>(
        where(c(&MapMarkInfo::mapId) == info.mapId and /* NOLINT */
              c(&MapMarkInfo::markType) == info.markType));
    if (markInfos.size() != 0) {
        // 已存在则替换
        printf("mapMark already exit mapId:{%s},markType:{%s}\r\n",
               info.mapId.c_str(), info.markType.c_str());
        tmp.markId = markInfos.at(0)->markId;
    }
    tmp.mapId = info.mapId;
    tmp.markType = info.markType;
    tmp.commit = commit;
    printf("replace,markId:{%d},mapId:{%s},markType:{%s} \r\n", tmp.markId,
           tmp.mapId.c_str(), tmp.markType.c_str());
    storage.replace(tmp);
}

std::string SqliteImpl::getMapMarkInfo(const std::string& mapId,
                                       const std::string& markType) {
    auto storage = getStorage();
    auto markPtr = storage.get_all_pointer<MapMarkInfo>(
        where(c(&MapMarkInfo::mapId) == mapId and /* NOLINT */
              c(&MapMarkInfo::markType) == markType));
    std::string ret = "";
    for (const auto& tmp : markPtr) {
        ret = tmp->commit;
    }
    return ret;
}

bool SqliteImpl::delMapMarkInfo(const std::string& mapId) {
    auto storage = getStorage();
    if (mapId != "") {
        storage.remove_all<MapMarkInfo>(where(c(&MapMarkInfo::mapId) == mapId));
    } else {
        storage.remove_all<MapMarkInfo>();
    }
    return true;
}

void SqliteImpl::setAreaMarkInfo(const std::string& mapId,
                                 AreaMarkType areaType,
                                 const std::vector<char>& points) {
    auto storage = getStorage();
    AreaMarkInfo areaTmp;
    areaTmp.areaData.clear();
    areaTmp.areaId = RAND_INT(10000);
    auto areaInfos = storage.get_all_pointer<AreaMarkInfo>(
        where(c(&AreaMarkInfo::mapId) == mapId and /* NOLINT */
              c(&AreaMarkInfo::areaType) == static_cast<int>(areaType)));
    if (areaInfos.size() != 0) {
        // 已存在则替换
        printf("areaMsg already exit mapId:{%s},markType:{%d}\r\n",
               mapId.c_str(), areaType);
        areaTmp.areaId = areaInfos.at(0)->areaId;
    }
    areaTmp.mapId = mapId;
    areaTmp.areaType = areaType;
    areaTmp.areaData = std::move(points);
    storage.replace(areaTmp);
}

std::vector<char> SqliteImpl::getAreaMarkInfo(const std::string& mapId,
                                              AreaMarkType areaType) {
    auto storage = getStorage();
    auto mapInfos = storage.get_all_pointer<AreaMarkInfo>(
        where(c(&AreaMarkInfo::mapId) == mapId and  // NOLINT
              c(&AreaMarkInfo::areaType) == static_cast<int>(areaType)));
    if (mapInfos.size() != 1) {
        printf("undefine map infos num : {%ld}", mapInfos.size());
        return {};
    }
    return mapInfos.at(0)->areaData;
}

bool SqliteImpl::delAreaMarkInfo(const std::string& mapId,
                                 AreaMarkType areaType) {
    auto storage = getStorage();
    if (areaType == ALL_AREA) {
        storage.remove_all<AreaMarkInfo>(
            where(c(&AreaMarkInfo::mapId) == mapId));
    } else {
        storage.remove_all<AreaMarkInfo>(
            where(c(&AreaMarkInfo::mapId) == mapId and  // NOLINT
                  c(&AreaMarkInfo::areaType) == static_cast<int>(areaType)));
    }
    return true;
}

};  // namespace pig_sqlite
