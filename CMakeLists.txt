cmake_minimum_required(VERSION 3.20)

set(project_name ucichess) ## rename your project here

project(${project_name})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -Ofast")


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
target_include_directories(${project_name} PUBLIC uci)


add_executable(process test/process.cpp)
target_link_libraries(process ${project_name} )

add_executable(pipe test/file.cpp)
target_link_libraries(pipe ${project_name} )

add_executable(uci_test test/uci_test.cpp)
target_link_libraries(uci_test ${project_name} )
