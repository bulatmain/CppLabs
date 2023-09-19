include(${PROJECT_SOURCE_DIR}/cmake/gtest.cmake)

add_executable(lab1-unit-tests test.cpp)

target_link_libraries(lab1-unit-tests
    PRIVATE
        Lab1::headers
        GTest::GTest
)

add_custom_target(check ALL COMMAND lab1-unit-tests)
