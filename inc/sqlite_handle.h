#include <memory>

#include "pig_sqlite.h"

namespace pig_sqlite {

class SqliteHandler {
public:
    SqliteHandler();
    ~SqliteHandler();

public:
    bool init();

private:
    std::shared_ptr<SqliteImpl> m_impl;
};

};  // namespace pig_sqlite
