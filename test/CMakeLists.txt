add_executable(${SWEEP_TEST_EXECUTABLE} "sweep-test.cpp")
add_executable(${GENERATE_VISUALIZATION_EXECUTABLE} "generate_visualization.cpp")

target_link_libraries(${SWEEP_TEST_EXECUTABLE}
        PUBLIC
            ${CORE_LIBRARY}        
)
target_link_libraries(${GENERATE_VISUALIZATION_EXECUTABLE}
        PUBLIC
            ${CORE_LIBRARY}        
)


add_executable(unit_tests "test.cpp")

target_link_libraries(unit_tests
        PRIVATE
            ${CORE_LIBRARY}
            GTest::gtest_main
)

add_custom_target(run_unit_tests
        COMMAND unit_tests
        DEPENDS unit_tests
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
