
###### cui chess
find_package(fmt)


list(APPEND TESTS_UCI uci_test engine_spin_test unifex_test stdexec_test stdexec_hello)

foreach(test IN LISTS TESTS_UCI)
        add_executable(${test} "ucichess/${test}.cpp" )
        set_target_properties(${test} PROPERTIES
                CXX_STANDARD 20
                CXX_STANDARD_REQUIRED ON
        )
        target_link_libraries(${test} ${project_name} fmt::fmt expected-lite unifex stdexec)
        add_dependencies(${test} ${project_name})
endforeach()




###### ux

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




