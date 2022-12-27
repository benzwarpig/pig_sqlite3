#include <iostream>
#include <string>

#include "build_info.h"
#include "pig_serialize.hpp"
#include "sqlite_handle.h"

using namespace pig_sqlite;
using pig_util::pig_serialize::PigSerialize;

int main() {
    std::cout << "hello sqlite3" << std::endl;
    printf("Pig Version : {%s} \r\n", gPigSqliteVersion);
    printf("Pig git branch : {%s} \r\n", gGitBranch);
    printf("Pig git commit : {%s} \r\n", gGitCommit);
    printf("Pig build time : {%s} \r\n", gBuildTime);
    pig_sqlite::SqliteHandler pigSqlite;
    if (!pigSqlite.init()) {
        printf("pig sqlite init failure !!!");
    }
    printf("\r\n");

#if 0
    pigSqlite.setPigSlogan("benzs_war_pig");
    auto slogan = pigSqlite.getPigSlogan();

    printf("pig_slogan is : {%s}\r\n", slogan.c_str());
#endif

#if 0
    pigSqlite.setMapMarkInfo("map_1", "collide", "333 this is map_1 collide");
    pigSqlite.setMapMarkInfo("map_2", "collide", "333 this is map_2 collide");
    pigSqlite.setMapMarkInfo("map_2", "cliff", "666 this is map_2 collide");

    printf("map_1_collide : %s \r\n",
           pigSqlite.getMapMarkInfo("map_1", "collide").c_str());

    pigSqlite.delMapMarkInfo("map_2");
#endif

#if 1
    std::vector<Point2D> points;
    Point2D point;
    point = {0, 0};
    points.emplace_back(point);
    point = {1, 1};
    points.emplace_back(point);
    point = {2, 2};
    points.emplace_back(point);
    point = {3, 3};
    points.emplace_back(point);
    point = {4, 4};
    points.emplace_back(point);
    point = {5, 5};
    points.emplace_back(point);

    pigSqlite.setAreaMarkInfo("map_123456", AreaMarkType::ROOM, points);
    printf("删除之前\r\n");
    auto readPoints =
        pigSqlite.getAreaMarkInfo("map_123456", AreaMarkType::ROOM);
    for (const auto& tmp : readPoints) {
        printf("point,x:{%f},y:{%f}\r\n", tmp.x(), tmp.y());
    }

    pigSqlite.delAreaMarkInfo("map_123456", AreaMarkType::ALL_AREA);
    printf("删除之后\r\n");
    readPoints = pigSqlite.getAreaMarkInfo("map_123456", AreaMarkType::ROOM);
    for (const auto& tmp : readPoints) {
        printf("point,x:{%f},y:{%f}\r\n", tmp.x(), tmp.y());
    }
#endif

    return 0;
}
