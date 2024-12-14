cmake_minimum_required(VERSION 3.30)

set(project_name ucichess) 

project(${project_name} VERSION 0.9.13 DESCRIPTION "UCI chess protocol adapter")

add_subdirectory(external)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)

