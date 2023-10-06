cmake_minimum_required(VERSION 3.14)

project(Lab2 LANGUAGES CXX)

option(LAB2_TESTING "Включить модульное тестирование" ON)

option(ENABLE_WARNING "Включить предупреждения" OFF)

if (ENABLE_WARNING)
    if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
        add_compile_options(
            -Wall
            -Wextra
            -Wpedantic

            -Wcast-align
            -Wcast-qual
            -Wconversion
            -Wctor-dtor-privacy
            -Wenum-compare
            -Wfloat-equal
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Woverloaded-virtual
            -Wredundant-decls
            -Wsign-conversion
            -Wsign-promo
        )
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_compile_options(/W4 /WX)
    endif()

    if(NOT CMAKE_CXX_EXTENSIONS)
        set(CMAKE_CXX_EXTENSIONS OFF)
    endif()
endif()   

add_library(Lab2_headers INTERFACE)
target_include_directories(Lab2_headers INTERFACE include)
add_library(Lab2::headers ALIAS Lab2_headers)


add_library(Lab2_source STATIC
    src/octalDigit.cpp
    src/octal.cpp
)
target_link_libraries(Lab2_source PUBLIC Lab2_headers)
target_compile_features(Lab2_source PRIVATE cxx_std_17)

add_library(Lab2::source ALIAS Lab2_source)


if(NOT LAB2_TESTING)
    message(STATUS "Тестирование выключено")
else()
    add_subdirectory(test)
endif()

