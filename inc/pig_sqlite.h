#include <sqlite_orm/sqlite_orm.h>

#include <iostream>
#include <string>

namespace pig_sqlite {

/**
 * @brief table_sys_info 系统信息(存储字典)
 * field: | name | value |
 */
struct SysInfo {
    std::string name;   // 主键
    std::string value;  // 值
};

struct MapMarkInfo {
    int markId;
    std::string mapId;
    std::string markType;
    std::string commit;
};

class SqliteImpl {
public:
    SqliteImpl();
    ~SqliteImpl();

    bool loadDB(const std::string& dbName);

    /***************** sysinfo 管理部分 *****************/
    // 设置单个SysInfo
    void setSysInfo(const std::string& name, const std::string& value);
    // 删除单个SysInfo
    bool delSysInfo(const std::string& name);
    // 获取单个SysInfo
    std::string getSysInfo(const std::string& name);
    // 获取所有的SysInfo
    std::map<std::string, std::string> getSysInfo();

    /*************** MapMarkInfo 管理部分 ***************/
    // 设置地图标记信息属性
    void setMapMarkInfo(const MapMarkInfo& info, const std::string& commit);

    // 获取地图标记属性
    std::string getMapMarkInfo(const std::string& mapId,
                               const std::string& markType);

    // 删除对应地图的标记信息
    bool delMapMarkInfo(const std::string& mapId);

private:
    auto getStorage();

private:
    std::string m_dbName;
    bool m_isLoad{false};

private:
    friend class SqliteHandler;
    static constexpr const char* k_pigSlogan{"pig_slogan"};
};

};  // namespace pig_sqlite
