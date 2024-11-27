cmake_minimum_required(VERSION 3.20)

set(project_name ucichess) 

project(${project_name} VERSION 0.9.3 DESCRIPTION "UCI chess protocol adapter")

add_library(${project_name}
            SHARED
            src/process/process.cpp
            src/process/process.hpp
            src/process/resource.cpp
            src/process/resource.hpp
            src/process/file.cpp
            src/process/file.hpp
            src/error/error.cpp
            src/error/error.hpp
            src/uci/command.cpp
            src/uci/command.hpp 
            src/uci/process.cpp
            src/uci/process.hpp
            src/uci/info.cpp
            src/uci/info.hpp
            )

set_target_properties(${project_name} PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(${project_name} PRIVATE .)


# ---- Install rules ----

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)


install(
    TARGETS ${project_name}
    EXPORT ${project_name}
    LIBRARY COMPONENT ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    
    )
install(FILES ${CMAKE_BINARY_DIR}/${project_name}.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

install(
    EXPORT ${project_name}
    NAMESPACE ${project_name}::
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT ${project_name}
)


configure_file( ${project_name}.pc.in  ${project_name}.pc @ONLY)


# Tests
# add_executable(process test/process.cpp)
# target_link_libraries(process ${project_name} )

# add_executable(pipe test/file.cpp)
# target_link_libraries(pipe ${project_name} )

# add_executable(uci_test test/uci_test.cpp)
# target_link_libraries(uci_test ${project_name} )
#I followed this link.
#https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake

