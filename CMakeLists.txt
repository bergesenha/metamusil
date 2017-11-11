cmake_minimum_required(VERSION 2.8)


project(metamusil CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(METAMUSIL_BUILD_TESTS "Build unit tests" OFF)

add_library(metamusil INTERFACE)
target_compile_features(metamusil
    INTERFACE cxx_std_14)
target_include_directories(metamusil
    INTERFACE include/
    )

if(METAMUSIL_BUILD_TESTS)
    set(METAMUSIL_TEST_SRC
        tests/test_main.cpp
        tests/test_type_list.cpp
        tests/test_function_deduction.cpp
        tests/test_member_variable_deduction.cpp
        tests/test_sfinae.cpp
        tests/test_integer_sequence.cpp
        tests/test_misc.cpp
        tests/test_type_descriptor.cpp
        )
    add_executable(unit_tests ${METAMUSIL_TEST_SRC})
    target_include_directories(unit_tests
        PRIVATE external/Catch/include/
        )
    target_link_libraries(unit_tests metamusil)
endif(METAMUSIL_BUILD_TESTS)
