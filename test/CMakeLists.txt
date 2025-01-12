
###### uci chess

find_package(fmt)


list(APPEND TESTS_UCI uci_test)

foreach(test IN LISTS TESTS_UCI)
        add_executable(${test} "ucichess/${test}.cpp" "ucichess/command.cpp" "ucichess/command.hpp" )
        set_target_properties(${test} PROPERTIES
                CXX_STANDARD 20
                CXX_STANDARD_REQUIRED ON
        )
        target_link_libraries(${test} ${project_name}-engine fmt::fmt)
        add_dependencies(${test} ${project_name}-engine )
endforeach()

