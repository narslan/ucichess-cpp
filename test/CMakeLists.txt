
###### cui chess


list(APPEND TESTS_UCI uci_test)

foreach(test IN LISTS TESTS_UCI)
        add_executable(${test} "ucichess/${test}.cpp" "ucichess/command.cpp" "ucichess/command.hpp" )
        set_target_properties(${test} PROPERTIES
                CXX_STANDARD 20
                CXX_STANDARD_REQUIRED ON
        )
        target_link_libraries(${test} ${project_name})
        add_dependencies(${test} ${project_name})
endforeach()




###### ux
find_package(fmt)

list(APPEND TESTS handling_mono_client handling_multiple_clients)

foreach(test IN LISTS TESTS)
        add_executable(${test} "ux/${test}.cpp" )
        set_target_properties(${test} PROPERTIES
                CXX_STANDARD 20
                CXX_STANDARD_REQUIRED ON
        )
        target_link_libraries(${test} ${project_name} fmt::fmt)
        add_dependencies(${test} ${project_name})
endforeach()



## pgn tests

list(APPEND TESTS_PGN pgn_test)

foreach(test IN LISTS TESTS_PGN)
        add_executable(${test} "pgn/${test}.cpp" )
        set_target_properties(${test} PROPERTIES
                CXX_STANDARD 23
                CXX_STANDARD_REQUIRED ON
        )
        target_link_libraries(${test} ${project_name})
        add_dependencies(${test} ${project_name})
endforeach()


