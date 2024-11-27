
add_executable(ucichess-tests ucichess/uci_test.cpp
)

set_target_properties(ucichess-tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(ucichess-tests
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(ucichess-tests ${project_name})
add_dependencies(ucichess-tests ${project_name})

