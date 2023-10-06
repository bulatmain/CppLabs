include(${PROJECT_SOURCE_DIR}/cmake/gtest.cmake)

#option(GTEST_DISABLE_PTHREADS "" OFF)

option(OCTALDIGIT_TESTING "" OFF)

option(OCTAL_TESTING "" ON)

if (NOT OCTALDIGIT_TESTING)
    message("Тестирование класса OctalDigit отключено!\n")
else()
    add_executable(lab2-octalDigit-utest octalDigitTest.cpp)
    target_link_libraries(lab2-octalDigit-utest 
        PRIVATE 
            Lab2::source
            GTest::GTest)
    add_custom_target(checkOctalDigit ALL COMMAND lab2-octalDigit-utest)
endif()

if (NOT OCTAL_TESTING)
    message("Тестирование класса Octal отключено!\n")
else()
    add_executable(lab2-octal-utest octalTest.cpp)
    target_link_libraries(lab2-octal-utest 
        PRIVATE 
            Lab2::source
            GTest::GTest)
    add_custom_target(checkOctal ALL COMMAND lab2-octal-utest)
endif()
