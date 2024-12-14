find_package(fmt)
# engine library

add_library(${project_name}-engine
            SHARED
            ucichess/ux/process.cpp
            ucichess/ux/process.hpp
            ucichess/ux/resource.cpp
            ucichess/ux/resource.hpp
            ucichess/ux/file.cpp
            ucichess/ux/file.hpp
            ucichess/ux/socket.cpp
            ucichess/ux/socket.hpp
            ucichess/error/error.cpp
            ucichess/error/error.hpp
            ucichess/uci/engine.cpp
            ucichess/uci/engine.hpp
                       )
set_target_properties(${project_name}-engine PROPERTIES
            CXX_STANDARD 20
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED ON
)
target_link_libraries(${project_name}-engine fmt::fmt)

target_include_directories(${project_name}-engine
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# pgn2sqlite library


add_library(${project_name}-pgn2sqlite
            SHARED
            ucichess/pgn/parse.cpp
            ucichess/pgn/parse.hpp
            ucichess/pgn/sqlite.cpp
            ucichess/pgn/sqlite.hpp
            )
set_target_properties(${project_name}-pgn2sqlite PROPERTIES
            CXX_STANDARD 20
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED ON
)
target_link_libraries(${project_name}-pgn2sqlite fmt::fmt SQLiteCpp)

 target_include_directories(${project_name}-pgn2sqlite
         PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
 )
