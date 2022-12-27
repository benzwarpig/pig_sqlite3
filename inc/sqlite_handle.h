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

    std::string getMapMarkInfo(const std::string& mapId,
                               const std::string& markType);

    bool delMapMarkInfo(const std::string& mapId = "");

    /* 区域信息标记部分 */
    // 设置区域信息标记部分
    void setAreaMarkInfo(const std::string& mapId, AreaMarkType areaType,
                         const std::vector<Point2D>& points);

    // 获取对应地图区域信息标记部分
    std::vector<Point2D> getAreaMarkInfo(const std::string& mapId,
                                         AreaMarkType areaType);

    // 删除区域标记信息
    bool delAreaMarkInfo(const std::string& mapId, AreaMarkType areaType);

private:
    std::shared_ptr<SqliteImpl> m_impl;
};

};  // namespace pig_sqlite
