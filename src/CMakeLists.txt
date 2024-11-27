
add_library(${project_name}
            SHARED
            ucichess/process/process.cpp
            ucichess/process/process.hpp
            ucichess/process/resource.cpp
            ucichess/process/resource.hpp
            ucichess/process/file.cpp
            ucichess/process/file.hpp
            ucichess/error/error.cpp
            ucichess/error/error.hpp
            ucichess/uci/command.cpp
            ucichess/uci/command.hpp 
            ucichess/uci/process.cpp
            ucichess/uci/process.hpp
            ucichess/uci/info.cpp
            ucichess/uci/info.hpp
            )

set_target_properties(${project_name} PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED ON
)

target_include_directories(${project_name}
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
