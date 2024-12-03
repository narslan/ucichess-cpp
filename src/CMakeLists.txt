
add_library(${project_name}
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
            ucichess/uci/command.cpp
            ucichess/uci/command.hpp 
            ucichess/uci/process.cpp
            ucichess/uci/process.hpp
            ucichess/uci/options.cpp
            ucichess/uci/options.hpp
            )

set_target_properties(${project_name} PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED ON
)

target_include_directories(${project_name}
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
