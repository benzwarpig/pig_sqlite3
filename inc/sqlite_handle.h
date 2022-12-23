#include <memory>

#include "pig_sqlite.h"

namespace pig_sqlite {

class SqliteHandler {
public:
    SqliteHandler();
    ~SqliteHandler();

public:
    bool init();

    bool setPigSlogan(const std::string& value);

    bool delPigSlogan();

    std::string getPigSlogan();

    void setMapMarkInfo(const std::string& mapId, const std::string& markType,
                        const std::string& commit);

    bool delMapMarkInfo(const std::string& mapId);

private:
    std::shared_ptr<SqliteImpl> m_impl;
};

};  // namespace pig_sqlite
