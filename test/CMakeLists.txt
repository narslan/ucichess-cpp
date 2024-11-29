
add_executable(ucichess-tests ucichess/uci_test.cpp
)

set_target_properties(ucichess-tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(ucichess-tests
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
      
)
find_package(fmt)
target_link_libraries(ucichess-tests ${project_name}   fmt::fmt)
add_dependencies(ucichess-tests ${project_name})

###### ux
find_package(fmt)

list(APPEND TESTS handling_mono_client handling_multiple_clients)

foreach(test IN LISTS TESTS)
        add_executable(${test} "ux/${test}.cpp" )
        set_target_properties(${test} PROPERTIES
                CXX_STANDARD 17
                CXX_STANDARD_REQUIRED ON
        )
        target_link_libraries(${test} ${project_name} fmt::fmt)
        add_dependencies(${test} ${project_name})
endforeach()




