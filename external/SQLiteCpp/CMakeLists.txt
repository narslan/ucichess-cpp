cmake_minimum_required(VERSION 3.24)
set(CMAKE_C_STANDARD 11)

set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
# 1. Fetch Photon repo with specific tag or branch
include(FetchContent)
FetchContent_Declare(
    SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SQLiteCpp)

# 2. Submodule
# add_subdirectory(photon)
