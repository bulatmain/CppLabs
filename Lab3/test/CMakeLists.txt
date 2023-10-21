include(${PROJECT_SOURCE_DIR}/cmake/gtest.cmake)

function(OPTION_TURN_ON_TESTING 
    CONDITION TEST_NAME TEST_SOURCE EXEC_TARGET_NAME)
    if (NOT ${CONDITION})
        message("Тестирование класса OctalDigit отключено!\n")
    else()
        add_executable(${TEST_NAME} ${TEST_SOURCE})
        target_link_libraries(${TEST_NAME} 
            PRIVATE 
                Lab3::source
                GTest::GTest)
        add_custom_target(${EXEC_TARGET_NAME} ALL COMMAND ${TEST_NAME})
    endif()    

endfunction()

option(GTEST_DISABLE_PTHREADS "" OFF)

option(FLAT_VECTOR_TESTING "" OFF)

option(QUADRILITERAL_TESTING "" ON)

OPTION_TURN_ON_TESTING(FLAT_VECTOR_TESTING lab3-flat_vector-utest flat_vector_test.cpp checkFlatVector)

OPTION_TURN_ON_TESTING(QUADRILITERAL_TESTING lab3-quad-utest quad_test.cpp checkQuad)

