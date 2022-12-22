pwd

CMD_PATH=`realpath $0`
CMD_DIR=`dirname ${CMD_PATH}`
build_info_file="build_info.h.in"

cd ${CMD_DIR}
rm -f $build_info_file

cur_time=$(date "+%Y%m%d%H%M%S")
git_commit=$(git log --pretty=format:"%h" -1 )
git_branch=$(git branch | sed -n '/\* /s///p')
pig_version="$git_commit-$cur_time"
pwd

echo "#ifndef __PIG_SQLITE_VERSION_H" > $build_info_file
echo "#define __PIG_SQLITE_VERSION_H" >> $build_info_file
echo "#define CURRENT_PATH \"@CURRENT_PATH@\"" >> $build_info_file
echo "static constexpr const char* gPigSqliteVersion=\"$pig_version\";" >> $build_info_file
echo "static constexpr const char* gGitBranch=\"$git_branch\";" >> $build_info_file
echo "static constexpr const char* gGitCommit=\"$git_commit\";" >> $build_info_file
echo "static constexpr const char* gBuildTime=\"$cur_time\";" >> $build_info_file
echo "#endif" >> $build_info_file
cat $build_info_file

pwd
