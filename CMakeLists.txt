cmake_minimum_required(VERSION 3.20)

set(project_name ucichess) 

project(${project_name} VERSION 0.9.3 DESCRIPTION "UCI chess protocol adapter")


add_subdirectory(src)
enable_testing()
add_subdirectory(test)

# set_target_properties(${project_name} PROPERTIES VERSION ${PROJECT_VERSION})
# target_include_directories(${project_name} PRIVATE .)


# # ---- Install rules ----

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

