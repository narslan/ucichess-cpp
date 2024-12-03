cmake_minimum_required(VERSION 3.30)

set(project_name ucichess) 

project(${project_name} VERSION 0.9.3 DESCRIPTION "UCI chess protocol adapter")

add_subdirectory(src)
add_subdirectory(external)

enable_testing()
add_subdirectory(test)

# set_target_properties(${project_name} PROPERTIES VERSION ${PROJECT_VERSION})
# target_include_directories(${project_name} PRIVATE .)


# # ---- Install rules ----

