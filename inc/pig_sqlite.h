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

class SqliteImpl {
public:
    SqliteImpl();
    ~SqliteImpl();

    bool loadDB(const std::string& dbName);

private:
    auto getStorage();

private:
    std::string m_dbName;
    bool m_isLoad{false};

private:
    static constexpr const char* k_pigSlogan = "pig_slogan";
};

};  // namespace pig_sqlite
