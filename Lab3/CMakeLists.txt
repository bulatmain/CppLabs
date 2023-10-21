cmake_minimum_required(VERSION 3.14)

project(Lab3 LANGUAGES CXX)

option(LAB3_TESTING "Включить модульное тестирование" ON)

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

add_library(Lab3_headers INTERFACE)
target_include_directories(Lab3_headers INTERFACE include)
add_library(Lab3::headers ALIAS Lab3_headers)

add_library(Lab3_source STATIC
    src/figure.cpp
    src/quadrilateral.cpp
    src/rectangle.cpp
    src/rhombus.cpp
    src/trapeze.cpp
    src/flat_vector.cpp
)
target_link_libraries(Lab3_source PUBLIC Lab3_headers)
target_compile_features(Lab3_source PRIVATE cxx_std_17)

add_library(Lab3::source ALIAS Lab3_source)


add_executable(exec src/main.cpp)

target_link_libraries(exec PRIVATE Lab3_source)

if(NOT LAB3_TESTING)
    message(STATUS "Тестирование выключено")
else()
    add_subdirectory(test)
endif()

