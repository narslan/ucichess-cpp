cmake_minimum_required(VERSION 3.20)

set(project_name ucichess) 

project(${project_name} VERSION 0.9 DESCRIPTION "UCI chess protocol adapter")

add_library(${project_name}
            SHARED
            process/process.cpp
            process/process.hpp
            process/resource.cpp
            process/resource.hpp
            process/file.cpp
            process/file.hpp
            error/error.cpp
            error/error.hpp
            uci/command.cpp
            uci/command.hpp 
            uci/process.cpp
            uci/process.hpp
            uci/info.cpp
            uci/info.hpp
            )

set_target_properties(${project_name} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${project_name} PROPERTIES PUBLIC_HEADER uci/process.hpp)



add_executable(process test/process.cpp)
target_link_libraries(process ${project_name} )

add_executable(pipe test/file.cpp)
target_link_libraries(pipe ${project_name} )

add_executable(uci_test test/uci_test.cpp)
target_link_libraries(uci_test ${project_name} )
