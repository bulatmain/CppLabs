cmake_minimum_required(VERSION 3.14)

project(lab5 LANGUAGES CXX)
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-g)

option(LAB5_TESTING "Включить модульное тестирование" ON)

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

add_library(lab5_headers INTERFACE)
target_include_directories(lab5_headers INTERFACE headers)
add_library(lab5::headers ALIAS lab5_headers)

add_executable(exec exec/main.cpp)
target_link_libraries(exec PRIVATE lab5::headers)
# target_compile_features(exec PRIVATE cxx_std_14)

if(NOT LAB5_TESTING)
    message(STATUS "Тестирование выключено")
else()
    add_subdirectory(test)
endif()

