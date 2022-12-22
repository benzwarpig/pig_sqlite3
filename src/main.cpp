#include <iostream>
#include <string>

#include "build_info.h"
#include "sqlite_handle.h"

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

    pigSqlite.setPigSlogan("benzs_war_pig");
    auto slogan = pigSqlite.getPigSlogan();

    printf("pig_slogan is : {%s}\r\n", slogan.c_str());

    pigSqlite.delPigSlogan();
    slogan = pigSqlite.getPigSlogan();
    printf("pig_slogan is : {%s}\r\n", slogan.c_str());

    return 0;
}
