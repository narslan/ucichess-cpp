
add_executable(ucichess-tests ucichess/tests.cpp
)

set_target_properties(ucichess-tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(ucichess-tests
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_dependencies(ucichess-tests ${UCICHESS_NAME})

target_link_oatpp(ucichess-tests)

target_link_libraries(ucichess-tests
        PRIVATE ${OATPP_THIS_ucichess_NAME}
      
)

add_test(ucichess-tests ucichess-tests)
