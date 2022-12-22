#include <pig_sqlite.h>

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
                   make_column("value", &SysInfo::value)));

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

};  // namespace pig_sqlite
