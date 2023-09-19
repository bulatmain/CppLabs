cmake_minimum_required(VERSION 3.14)

project(Lab1 LANGUAGES CXX)

option(LAB1_TESTING "Включить модульное тестирование" ON)

if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(
        -Werror

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



add_library(lab1_headers INTERFACE)
target_include_directories(lab1_headers INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_compile_features(lab1_headers INTERFACE cxx_std_17)

add_library(Lab1::headers ALIAS lab1_headers)


add_executable(lab1_main src/main.cpp)

target_link_libraries(lab1_main PUBLIC lab1_headers)



if(NOT LAB1_TESTING)
    message(STATUS "Тестирование выключено")
else()
    add_subdirectory(test)
endif()

