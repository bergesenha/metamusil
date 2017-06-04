cmake_minimum_required(VERSION 2.8)


project(metamusil CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(main src/main.cpp)
target_compile_features(main
    PRIVATE cxx_std_14)
target_include_directories(main
    PRIVATE include/
    )
